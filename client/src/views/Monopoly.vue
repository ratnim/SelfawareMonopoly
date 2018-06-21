<template>
<div class="home">
  <h1>Monopoly</h1> Hi {{nickname}}
  <div v-for="player in players">{{player}}</div>
  <div class="">
    <md-button @click="rollDice()">ROLL THE DICE</md-button>
    <span>{{dice1}}, {{dice2}}</span>
  </div>
  <div class="">
    <easel-canvas width="600" height="600" ref="stage">
      <!--from LOS to prison -->
      <MonopolyField v-for="(field, index) in lane1" :x="10" :y="10+fieldLength+index*fieldLength" :fieldWidth="fieldWidth" :fieldLength="fieldLength" :align="['bottom', 'left']" :label="field.label" :attributes="field.attributes"></MonopolyField>
      <!--from prison to free parking -->
      <MonopolyField v-for="(field, index) in lane2" :x="10+index*fieldLength" :y="10" :fieldWidth="fieldWidth" :fieldLength="fieldLength":label="field.label" :attributes="field.attributes"></MonopolyField>
      <!-- from free parking to goto prison -->
      <MonopolyField v-for="(field, index) in lane3" :x="600-10-fieldLength" :y="10+index*fieldLength" :fieldWidth="fieldWidth" :fieldLength="fieldLength" :align="['bottom', 'right']" :label="field.label" :attributes="field.attributes"></MonopolyField>
      <!-- from goto prision to los -->
      <MonopolyField v-for="(field, index) in lane4" :x="10+fieldLength+index*fieldLength" :y="600-10-fieldLength"  :fieldWidth="fieldWidth" :fieldLength="fieldLength" :label="field.label" :attributes="field.attributes"></MonopolyField>

      <!--the players -->
      <MonopolyPlayer v-for="player in players" :key="player.nickname" :color="player.color" :fieldLength="fieldLength" ref="players"></MonopolyPlayer>
    </easel-canvas>
  </div>
  <div class="">
    <md-button @click="setReady()">READY</md-button>
    <md-button @click="endTurn()">END TURN</md-button>
    <md-button @click="startGame()">START GAME</md-button>
  </div>
</div>
</template>

<script>
import {
  mapGetters
} from 'vuex'

import * as gameConnection from '../storePlugins/gameConnection'

import MonopolyField from '@/components/MonopolyField'
import MonopolyPlayer from '@/components/MonopolyPlayer'

import game from '@/assets/game.json'

export default {
  name: 'monopoly',
  components: {
    MonopolyField,
    MonopolyPlayer
  },
  data: function() {
    return {
      fieldWidth: (600-10-10)/(game.fields[0].length+1),
      fieldLength: (600-10-10)/(game.fields[0].length+1),
      game: game,
      dice1 : null,
      dice2 : null,
      players : []
    }
  },
  computed: {
    ...mapGetters({
      tokens: 'getTokens',
      nickname: 'getNickname',
      sessionId: 'getSessionId'
    }),
    lane1: () => [].concat(game.fields[0]).reverse(),
    lane2: () => game.fields[1],
    lane3: () => game.fields[2],
    lane4: () => [].concat(game.fields[3]).reverse(),
  },

  created() {
    gameConnection.connect(this.$route.query.game_id, this.sessionId);
    gameConnection.joinGame();

    gameConnection.onDiceRolled(this.onDiceRolled);
    gameConnection.onPlayerJoined(this.onPlayerJoined);
    gameConnection.onPlayerMoved(this.onPlayerMoved);
    gameConnection.onPlayerReady(this.onPlayerReady);
    gameConnection.onGameStarted(this.onGameStarted);
    gameConnection.onGameEnded(this.onGameEnded);
    gameConnection.onTurnChanged(this.onTurnChanged);
    gameConnection.onError(this.onError);
  },
  beforeRouteLeave(to, from, next) {
    gameConnection.disconnect();
    next();
  },

  methods: {
    rollDice : function() {
      gameConnection.rollDice();
    },
    setReady : function() {
      gameConnection.setReady();
    },
    startGame : function() {
      gameConnection.startGame();
    },
    endTurn : function() {
      gameConnection.endTurn();
    },

    onDiceRolled : function(dice) {
      this.dice1 = dice[0];
      this.dice2 = dice[1];
    },
    onPlayerJoined : function(playerName) {
      console.log(playerName);
      this.players.push({currentField: 0, nickname: playerName, color: 'yellow'});
    },
    onPlayerMoved : function(playerName, distance) {
      for (var i = 0; i < this.players.length; i++) {
        if (this.players[i].nickname == playerName) {
          console.log(this.players[i].currentField);
          this.players[i].currentField = (this.players[i].currentField + distance) % 40;
          console.log(this.players[i].currentField);
          this.$refs.players[i].move(this.players[i].currentField);
        }
      }
    },
    onPlayerReady : function(playerName) {
      console.log(playerName + ' is now ready!');
    },
    onGameStarted : function() {
      console.log('Game started!');
    },
    onGameEnded : function() {
      console.log('Game ended');
    },
    onTurnChanged : function(playerName) {
      console.log('It\'s ' + playerName + ' turn!');
    },
    onError : function(message) {
      console.log(message);
    }
  }
}
</script>
