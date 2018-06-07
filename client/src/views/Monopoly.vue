<template>
<div class="home">
  <h1>Monopoly</h1> Hi {{nickname}}
  <div v-for="player in players">{{player}}</div>
  <div class="">
    <md-button @click="rollDice()">ROLL THE DICE</md-button>
    <span>{{dice1}}, {{dice2}}</span>
    <md-button @click="move()">MOVE</md-button>
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
      players : [{currentField: 0, nickname: this.nickname, color: 'yellow' }]
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

    gameConnection.onPlayerJoined(this.onPlayerJoined);
    gameConnection.onError(this.onError);
  },
  beforeRouteLeave(to, from, next) {
    gameConnection.disconnect();
    next();
  },

  methods: {
    rollDice : function() {
      //TODO get dices result from server
      this.dice1 = Math.floor(Math.random()*6)+1;
      this.dice2 = Math.floor(Math.random()*6)+1;

    },
    move : function() {
      this.players[0].currentField += this.dice1 + this.dice2
      this.$refs.players[0].move(this.players[0].currentField)
    },
    onPlayerJoined : function(playerName) {
      console.log(playerName);
      players.push({currentField: 0, nickname: playerName, color: 'yellow'});
    },
    onError : function(message) {
      console.log(message);
    }
  }
}
</script>
