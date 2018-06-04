<template>
<div class="md-content">
  <h1>The Lobby</h1>
  <div class="md-layout md-alignment-top-center">
    <md-steppers :md-active-step.sync="stepper.active" md-linear>
      <md-step id="first" md-label="Enter your Nickname" :md-done.sync="stepper.first">
        <div class="md-layout-item md-size-50 md-small-size-100 md-alignment-top-center">
          <form novalidate class="md-layout">
            <div class="md-layout md-gutter md-alignment-center-center">
              <div class="md-layout-item md-alignment-center-center">
                <md-field>
                  <label for="nickname">Nickname</label>
                  <md-input name="nickname" v-model="nickname" />
                </md-field>
              </div>
            </div>
          </form>
          <md-button class="md-raised md-primary" :disabled="!nickname" @click="setStepperDone('first', 'second')">join</md-button>
        </div>

      </md-step>

      <md-step id="second" md-label="Join a Game" :md-done.sync="stepper.second">
        <div class="md-layout-item md-size-50 md-small-size-100 md-alignment-top-center">
          <md-list class="md-double-line">
            <md-subheader>Open Games</md-subheader>

            <md-list-item v-for="game in games">
              <div class="md-list-item-text">
                <span>{{game.game_label}}</span>
                <span>
                  <span v-for="(player, index) in game.player_list">{{player}}<span v-if="index < game.player_list.length-1">, </span>
                  </span>
                </span>
              </div>
              <md-button @click="join(game.game_id)" class="md-icon-button md-list-action">
                <md-icon>forward</md-icon>
              </md-button>
            </md-list-item>
          </md-list>
          <md-button @click="newGame()" class="md-primary">create new game</md-button>
        </div>
      </md-step>
    </md-steppers>
  </div>
</div>
</template>

<script>

import {
  mapGetters
} from 'vuex'


export default {
  name: 'lobby',
  data: function() {
    return {
      stepper: {
        'active': 'first',
        first: false,
        second: false
      },
      nickname: ''
    }
  },
  computed: {
    ...mapGetters({
      'games': 'getGameList'
    })
  },
  created() {
    //get list of games
    //this.games = games;
    //provide nickname
    this.nickname = this.$route.query.nickname || this.$store.state.nickname;

    //join lobby

    //button: create a new game

    //button: join game

  },
  mounted() {

  },
  beforeRouteLeave(to, _from, next) {
    next();
  },
  methods: {
    setStepperDone(id, active) {
      this.stepper[id] = true;
      this.stepper.active = active;
      this.$store.dispatch('setNickname', this.nickname);
      //this.$socket.emit("enter_lobby", { player_name: this.nickname });
    },
    join(gameid) {
      this.$router.push({ name: 'monopoly', params: { gameid }, query: {test: 1}})
    },
    newGame() {
      console.log("new game");

    }
  }
}
</script>
