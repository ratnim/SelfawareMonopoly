<template>
<div class="">


  <!--Dialogs-->
  <md-dialog-prompt :md-active.sync="showNewGameName"
  v-model="newGameName"
  md-title="Wie soll das neue Spiel heißen?"
  md-input-maxlength="30"
  :md-input-placeholder="nickname + '& friends'"
  md-confirm-text="Fertig"
  @md-confirm="onNewGameConfirm"/>

  <md-snackbar md-position="center" :md-duration="9000" :md-active.sync="showError" md-persistent>
      <span>{{errorMessage}}</span>
      <md-button class="md-warning" @click="showError = false">ok, Schade</md-button>
    </md-snackbar>
  <!--/Dialogs-->


  <div class="md-content">
    <h1>The Lobby</h1>
    <p>Gib deinen Spielernamen an und starte eine neue Runde Monopoly</p>

    <div>
      <div class="md-layout md-alignment-top-center">
        <md-steppers :md-active-step.sync="stepper.active" md-linear>
          <md-step id="first" md-label="Enter your Nickname" :md-done.sync="stepper.first">
            <div class="md-layout-item md-size-50 md-small-size-100 md-alignment-top-center">
              <form novalidate class="md-layout">
                <div class="md-layout md-gutter md-alignment-center-center">
                  <div class="md-layout-item md-alignment-center-center">
                    <md-field>
                      <label for="nickname">Nickname</label>
                      <md-input ref="nickname" name="nickname" v-model="nickname" />
                    </md-field>
                  </div>
                </div>
              </form>
              <md-button class="md-raised md-primary" :disabled="!nickname" @click="createAccount()">join</md-button>
            </div>

          </md-step>

          <md-step id="second" md-label="Join a Game" :md-done.sync="stepper.second">
            <div class="md-layout-item md-size-50 md-small-size-100 md-alignment-top-center">
              <div class="md-layout md-alignment-top-center">
                <md-list class="md-double-line">
                  <md-subheader>Open Games</md-subheader>

                  <md-list-item v-for="game in games">
                    <div class="md-list-item-text">
                      <span>{{game.game_label}}</span>
                      <span>{{statusMap[game.game_status]}}</span>
                      <span>
                      <span v-for="(player, index) in game.player_list">{{player}}<span v-if="index < game.player_list.length-1">, </span>
                      </span>
                      </span>
                    </div>
                    <md-button @click="onJoinGame(game.game_id)" class="md-icon-button md-list-action">
                      <md-icon>forward</md-icon>
                    </md-button>
                  </md-list-item>
                </md-list>
                <md-button @click="createGame()" class="md-primary">create new game</md-button>
              </div>
            </div>
          </md-step>
        </md-steppers>
      </div>
    </div>
  </div>
</div>
</template>

<script>
import {
  mapGetters
} from 'vuex'

import LobbyConnection from '@/sockets/lobbyConnection';
import HomeConnection from '@/sockets/homeConnection';


export default {
  name: 'lobby',
  data: function() {
    return {
      lobbyConnection: null,
      homeConnection: null,
      stepper: {
        'active': 'first',
        first: false,
        second: false
      },
      statusMap: ["Open", "Started", "Ended"],
      showNewGameName: false,
      newGameName: '',
      games: [],
      showError: false,
      errorMessage: '',
      nickname: ''
    }
  },
  computed: {
    ...mapGetters({
      sessionId: 'getSessionId'
    })
    // nickname: {
    //   get: function() {
    //     return this.$store.getNickname();
    //   },
    //   set: function(newName) {
    //     this.$store.commit("setNickname", newName);
    //   }
    // }
  },

  created() {
    this.nickname = this.$route.query.nickname || this.$store.state.nickname;
    this.homeConnection = new HomeConnection({
      enter_lobby: this.onAccountCreated,
      error: this.onError
    });
    if (this.nickname && this.sessionId) { //skip the first step
      this.onAccountCreated({data: {session: this.sessionId}});
    }
  },
  beforeRouteLeave(to, from, next) {
    if (this.lobbyConnection) {
      this.lobbyConnection.disconnect();
    }
    this.homeConnection.disconnect();
    next();
  },

  methods: {
    createAccount() {
      console.log(this.nickname);
      this.homeConnection.createAccount(this.nickname);
    },
    onAccountCreated(data) {
      this.stepper['first'] = true; //mark first step as done
      this.stepper.active = 'second'; //mark second step as active
      this.$store.dispatch('createAccount', this.nickname);
      this.$store.commit('setSessionId', data.session);
      var handlers = {
        game_list: this.setGameList,
        create_game: this.onGameCreated
      };
      this.lobbyConnection = new LobbyConnection(data.session, handlers);
    },
    createGame() {
      this.showNewGameName = true;
    },
    onJoinGame(gameId) {
      this.$router.push({
        name: 'monopoly',
        query: {
          game_id: gameId
        }
      })
    },
    onNewGameConfirm() {
      this.lobbyConnection.createGame(this.newGameName);
      this.showNewGameName = false;
    },
    onGameCreated(data) {
      this.onJoinGame(data.game_id);
    },
    setGameList(data) {
      this.games = data.games;
    },
    onError: function(data) {
      console.log(data);
      this.showError = true;
      this.errorMessage = data.message;
    }
  }
}
</script>
