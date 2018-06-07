<template>
<div class="md-content">
  <h1>The Lobby</h1>
  <div class="md-layout md-alignment-top-center">
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
        <md-button @click="joinGame(game.game_id)" class="md-icon-button md-list-action">
          <md-icon>forward</md-icon>
        </md-button>
      </md-list-item>
    </md-list>
    <md-button @click="createGame()" class="md-primary">create new game</md-button>
  </div>
</div>
</template>

<script>

import {
  mapGetters
} from 'vuex'

import * as lobbyConnection from '../storePlugins/lobbyConnection'


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
      games: 'getGameList',
      sessionId: 'getSessionId'
    })
  },

  created() {
    lobbyConnection.connect(this.sessionId);
    lobbyConnection.onCreateGame(this.joinGame);
    lobbyConnection.onError(this.error);
  },
  beforeRouteLeave(to, from, next) {
    lobbyConnection.disconnect();
    next();
  },

  methods: {
    joinGame(gameId) {
      this.$router.push({ name: 'monopoly', query: { game_id: gameId } })
    },
    createGame(name) {
      lobbyConnection.createGame('test');
    },
    error: function(message) {
      console.log(message);
    }
  }
}
</script>
