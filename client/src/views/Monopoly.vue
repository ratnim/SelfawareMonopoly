<template>
<div class="home">
  <div class="md-layout">
    <div class="md-layout-item md-size-15">
      <h3>Alles was du wissen musst</h3>
      <div ref="a">
        Du bist {{nickname}}
      </div>
      <div  ref="a">
        Deine Gegner sind
        <div v-for="player in players" v-if="player.nickname != nickname">
          {{player.nickname}}
        </div>
      </div>
    </div>


      <div class="md-layout-item">
          <easel-canvas width="600" height="600" ref="stage">
            <!--from LOS to prison -->
            <MonopolyField ref="fields" :x="10" :y="600-10-fieldLength" :fieldWidth="fieldLength" :fieldLength="fieldLength" :align="['bottom', 'left']" :label="lane1[lane1.length-1].label" :attributes="lane1[lane1.length-1].attributes"></MonopolyField>
            <MonopolyField ref="fields" v-for="(field, index) in lane1" v-if="index != lane1.length-1" :x="10+index*0" :y="10+fieldLength+index*fieldWidth" :fieldWidth="fieldLength" :fieldLength="fieldWidth" :align="['bottom', 'left']" :label="field.label" :attributes="field.attributes"></MonopolyField>
            <!--from prison to free parking -->
            <MonopolyField ref="fields" :x="10" :y="10" :fieldWidth="fieldLength" :fieldLength="fieldLength" :align="['bottom', 'left']" :label="lane2[0].label" :attributes="lane2[0].attributes"></MonopolyField>
            <MonopolyField ref="fields" v-for="(field, index) in lane2" v-if="index != 0" :x="10+fieldLength+index*fieldWidth" :y="10+index*0" :fieldWidth="fieldLength" :fieldLength="fieldWidth" :label="field.label" :attributes="field.attributes" :rotation="90"></MonopolyField>
            <!-- from free parking to goto prison -->
            <MonopolyField ref="fields" :x="600-10-fieldLength" :y="10" :fieldWidth="fieldLength" :fieldLength="fieldLength" :align="['bottom', 'left']" :label="lane3[0].label" :attributes="lane3[0].attributes"></MonopolyField>
            <MonopolyField ref="fields" v-for="(field, index) in lane3" v-if="index != 0" :x="600-10-index*0" :y="10+index*fieldWidth+fieldLength" :fieldWidth="fieldLength" :fieldLength="fieldWidth"  :align="['bottom', 'right']"
              :label="field.label" :attributes="field.attributes" :rotation="180"></MonopolyField>
            <!-- from goto prision to los -->
            <MonopolyField ref="fields" :x="600-10-fieldLength" :y="600-10-fieldLength" :fieldWidth="fieldLength" :fieldLength="fieldLength" :align="['bottom', 'left']" :label="lane4[lane4.length-1].label" :attributes="lane4[lane4.length-1].attributes"></MonopolyField>
            <MonopolyField ref="fields" v-for="(field, index) in lane4" v-if="index != lane4.length-1" :x="10+fieldLength+index*fieldWidth" :y="600-10-index*0" :fieldWidth="fieldLength" :fieldLength="fieldWidth" :label="field.label" :attributes="field.attributes" :rotation="270"></MonopolyField>

            <!--the players -->
            <MonopolyPlayer v-for="player in players" :key="player.nickname" :color="player.color" :fieldLength="fieldLength" ref="players"></MonopolyPlayer>

        <Dice :x="300-30" :y="300" ref="dice1"></Dice>
        <Dice :x="300+30" :y="300" ref="dice2"></Dice>

        </easel-canvas>
    </div>
    <div class="md-layout-item md-size-15">
      <h2>Handle weise</h2>
      <md-button @click="rollDice()">ROLL THE DICE</md-button>
      <md-button @click="setReady()">READY</md-button>
      <md-button @click="endTurn()">END TURN</md-button>
      <md-button @click="startGame()">START GAME</md-button>
    </div>
  </div>
</div>
</template>

<script>
import {
  mapGetters
} from 'vuex'

import GameConnection from '@/sockets/gameConnection'

import MonopolyField from '@/components/MonopolyField'
import MonopolyPlayer from '@/components/MonopolyPlayer'
import Dice from '@/components/Dice'

import game from '@/assets/game.json'

export default {
  name: 'monopoly',
  components: {
    MonopolyField,
    MonopolyPlayer,
    Dice
  },
  data: function() {
    return {
      gameConnection: null,
      game: game,
      dice1: null,
      dice2: null,
      players: [],
      possible_actions: {

      },
      canvas: {
        margin: 2
      }
    }
  },
  computed: {
    ...mapGetters({
      tokens: 'getTokens',
      nickname: 'getNickname',
      sessionId: 'getSessionId'
    }),
    gamesFlatten: () => games.fields[0].concat(games.fields[1]).concat(games.fields[2]).concat(games.fields[3]),
    lane1: () => [].concat(game.fields[0]).reverse(),
    lane2: () => game.fields[1],
    lane3: () => game.fields[2],
    lane4: () => [].concat(game.fields[3]).reverse(),
    fieldWidth: () => (600 - 10 - 10) / (game.fields[0].length + 1 + 1), // + 1 because of l = 1.5*w
    fieldLength: () => (600 - 10 - 10) / (game.fields[0].length + 1 + 1) * 1.5,
  },

  created() {
    debugger;
    this.gameConnection = new GameConnection(this.$route.query.game_id, this.sessionId, {});
    // gameConnection.joinGame();
    //
    // gameConnection.onDiceRolled(this.onDiceRolled);
    // gameConnection.onPlayerJoined(this.onPlayerJoined);
    // gameConnection.onPlayerMoved(this.onPlayerMoved);
    // gameConnection.onPlayerReady(this.onPlayerReady);
    // gameConnection.onGameStarted(this.onGameStarted);
    // gameConnection.onGameEnded(this.onGameEnded);
    // gameConnection.onTurnChanged(this.onTurnChanged);
    // gameConnection.onError(this.onError);
  },
  beforeRouteLeave(to, from, next) {
    //gameConnection.disconnect();
    next();
  },

  methods: {
    rollDice: function() {
      this.$refs.dice1.animate();
      this.$refs.dice2.animate();
      this.gameConnection.rollDice();
    },
    setReady: function() {
      gameConnection.setReady();
    },
    startGame: function() {
      gameConnection.startGame();
    },
    endTurn: function() {
      gameConnection.endTurn();
    },

    onDiceRolled: function(dice) {
      this.$refs.dice1.show(dice[0]);
      this.$refs.dice2.show(dice[1]);
      this.dice1 = dice[0];
      this.dice2 = dice[1];
    },
    onPlayerJoined: function(playerName) {
      console.log(playerName);
      this.players.push({
        currentField: 0,
        nickname: playerName,
        color: this.getRandomColor()
      });
    },
    onPlayerMoved: function(playerName, distance) {
      for (var i = 0; i < this.players.length; i++) {
        if (this.players[i].nickname == playerName) {
          console.log(this.players[i].currentField);
          this.players[i].currentField = (this.players[i].currentField + distance) % 40;
          for (var j = 0; i < this.$refs.fields.length; j++) {
            if (this.$refs.fields[j].name == this.gamesFlatten[this.players[i].currentField].name) {
                this.$refs.players[i].move(this.$refs.fields[j].x, this.$refs.fields[j].y);
            }
          }
          console.log(this.players[i].currentField);

        }
      }
    },
    onPlayerReady: function(playerName) {
      console.log(playerName + ' is now ready!');
    },
    onGameStarted: function() {
      console.log('Game started!');
    },
    onGameEnded: function() {
      console.log('Game ended');
    },
    onTurnChanged: function(playerName) {
      console.log('It\'s ' + playerName + ' turn!');
    },
    onError: function(message) {
      console.log(message);
    },
    getRandomColor: function() {
      return "rgb(" + Math.round(Math.random()*255) + ", " + Math.round(Math.random()*255) + ", " + Math.round(Math.random()*255) + ")";

    }
  }
}
</script>
