<template>
<div class="home">
  <div class="md-layout">
    <div class="md-layout-item md-size-15">
      <h3>Alles was du wissen musst</h3>
      <div ref="a">
        Du bist {{nickname}}
      </div>
      <div ref="a">
        Deine Gegner sind
        <div v-for="player in players" v-if="player.nickname != nickname">
          {{player.nickname}}
        </div>
      </div>
    </div>

    <div class="md-layout-item">
      <easel-canvas width="600" height="600" ref="stage" v-if="lane1.length>0">
        <!--from LOS to jail -->
        <MonopolyField ref="fields" :x="10" :y="600-10-fieldLength" :fieldWidth="fieldLength" :fieldLength="fieldLength" :align="['bottom', 'left']" :label="lane1[lane1.length-1].name" :attributes="lane1[lane1.length-1].attributes"></MonopolyField>
        <MonopolyField ref="fields" v-for="(field, index) in lane1" v-if="index != lane1.length-1" :x="10+index*0" :y="10+fieldLength+index*fieldWidth" :fieldWidth="fieldLength" :fieldLength="fieldWidth" :align="['bottom', 'left']" :label="field.name" :attributes="field.attributes"></MonopolyField>
        <!--from prison to free parking -->
        <MonopolyField ref="fields" :x="10" :y="10" :fieldWidth="fieldLength" :fieldLength="fieldLength" :align="['bottom', 'left']" :label="lane2[0].name" :attributes="lane2[0].attributes"></MonopolyField>
        <MonopolyField ref="fields" v-for="(field, index) in lane2" v-if="index != 0" :x="10+fieldLength+index*fieldWidth" :y="10+index*0" :fieldWidth="fieldLength" :fieldLength="fieldWidth" :label="field.name" :attributes="field.attributes" :rotation="90"></MonopolyField>
        <!-- from free parking to goto prison -->
        <MonopolyField ref="fields" :x="600-10-fieldLength" :y="10" :fieldWidth="fieldLength" :fieldLength="fieldLength" :align="['bottom', 'left']" :label="lane3[0].name" :attributes="lane3[0].attributes"></MonopolyField>
        <MonopolyField ref="fields" v-for="(field, index) in lane3" v-if="index != 0" :x="600-10-index*0" :y="10+index*fieldWidth+fieldLength" :fieldWidth="fieldLength" :fieldLength="fieldWidth" :align="['bottom', 'right']" :label="field.name" :attributes="field.attributes"
          :rotation="180"></MonopolyField>
        <!-- from goto prision to los -->
        <MonopolyField ref="fields" :x="600-10-fieldLength" :y="600-10-fieldLength" :fieldWidth="fieldLength" :fieldLength="fieldLength" :align="['bottom', 'left']" :label="lane4[lane4.length-1].name" :attributes="lane4[lane4.length-1].attributes"></MonopolyField>
        <MonopolyField ref="fields" v-for="(field, index) in lane4" v-if="index != lane4.length-1" :x="10+fieldLength+index*fieldWidth" :y="600-10-index*0" :fieldWidth="fieldLength" :fieldLength="fieldWidth" :label="field.name" :attributes="field.attributes"
          :rotation="270"></MonopolyField>

        <!--the players -->
        <MonopolyPlayer v-for="player in players" :key="player.id" :color="player.color" :fieldLength="fieldLength" ref="monopolyPlayers"></MonopolyPlayer>


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

  <div class="">
    <h1>DEV TOOLS</h1>
    <md-button @click="__addFakePlayer()">add a fake player</md-button>



  </div>
</div>
</template>

<script>
import _ from 'lodash';

import {
  mapGetters
} from 'vuex'

import GameConnection from '@/sockets/gameConnection'
import HomeConnection from '@/sockets/homeConnection' // just for DEV
import LobbyConnection from '@/sockets/lobbyConnection' // just for DEV

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
      colorMapping: {
        0: "#527479",
        1: "#27C3A3",
        2: "#EDE591",
        3: "#89AE3D",
        4: "#F1B661",
        5: "#524090",
        6: "#AAC3A3",
        7: "#ED4591",
        8: "#E34B00"
      },
      dice1: null,
      dice2: null,
      players: [],
      lane1: [],
      lane2: [],
      lane3: [],
      lane4: [],
      possible_actions: {},
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
    fieldWidth: () => (600 - 10 - 10) / (10 + 1 + 1), // + 1 because of l = 1.5*w
    fieldLength: () => (600 - 10 - 10) / (10 + 1 + 1) * 1.5,
  },

  created() {
    let handlers = {
      "join_game": this.onPlayerJoined,
      "game_board": this.onGameboard,
      "possible_requests": this.onPossibleActions,
      "player_ready": this.onPlayerReady,
      "change_turn" : this.onTurnChanged,
      "money_change": this.onMoneyChange,
      "error": (data) => {console.log(data);}
    }
    this.gameConnection = new GameConnection(this.sessionId, this.$route.query.game_id, handlers);

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
      this.gameConnection.setReady();
    },
    startGame: function() {
      this.gameConnection.startGame();
    },
    endTurn: function() {
      this.gameConnection.endTurn();
    },

    onDiceRolled: function(dice) {
      this.$refs.dice1.show(dice[0]);
      this.$refs.dice2.show(dice[1]);
      this.dice1 = dice[0];
      this.dice2 = dice[1];
    },
    onPlayerJoined: function(data) {
      var playerName = data.player_name;
      if (_.findIndex(this.players, {
          'player_name': playerName
        }) == -1) {
        this.players.push({
          id: this.players.length,
          currentField: 0,
          nickname: playerName,
          color: this.getRandomColor()
        });
      };
      //translate players in game grafic
      if (this.$refs.monopolyPlayers) {
        let pCount = this.players.length;
        let step = 2*Math.PI/pCount;
        for (var i = 0; i < this.$refs.monopolyPlayers.length; i++) {
          this.$refs.monopolyPlayers[i].x = 2+this.fieldLength/2 + 25*Math.sin((i+1)*step);
          this.$refs.monopolyPlayers[i].y = 600-4-this.fieldLength/2-10 + 25*Math.cos((i+1)*step);
        }
      }

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
    onGameboard: function(data) {

      for (var i = 0; i < data.fields.length; i++) {
        data.fields[i].attributes = {
          color: this.colorMapping[data.fields[i].group]
        };
      }
      var gameboard = data.fields;
      this.lane1 = [].concat(gameboard.slice(0, 10)).reverse();
      this.lane2 = gameboard.slice(10, 20);
      this.lane3 = gameboard.slice(20, 30);
      this.lane4 = [].concat(gameboard.slice(30, 40)).reverse();
      this.$store.commit("setGame", gameboard);
    },
    onPossibleActions: function(data) {
      console.log("Possible Requests", data.requests);
    },
    onPlayerReady: function(data) {
      console.log(data.player_name + ' is now ready!');
    },
    onGameStarted: function() {
      console.log('Game started!');
    },
    onGameEnded: function() {
      console.log('Game ended');
    },
    onTurnChanged: function(data) {
      console.log('turn change!', data);
    },
    onMoneyChange: function(data) {
      console.log("Money change");
    },
    onError: function(message) {
      console.log(message);
    },
    getRandomColor: function() {
      return "rgb(" + Math.round(Math.random() * 255) + ", " + Math.round(Math.random() * 255) + ", " + Math.round(Math.random() * 255) + ")";

    },

    __addFakePlayer: function() {
      let gameConnection; //TODO add auto rolldice if roll dice in possible_actions
      let homeConnection = new HomeConnection({
        enter_lobby: (data) => {
          gameConnection = new GameConnection(data.session, this.$route.query.game_id, {
            "possible_requests": () => {this.rollDice();},
            "fallback": () => true,
            "error": () => true
          })
        }
      });
      setTimeout(() => homeConnection.createAccount("The Joker No." + Math.round(Math.random() * 1000)), 300);
      setTimeout(() => gameConnection.setReady(), 1000);
    }
  }
}
</script>
