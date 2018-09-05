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
        <span v-for="i in 1"> <!-- to make fields an array -->
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
        </span>

        <!--the players -->
        <MonopolyPlayer v-for="player in players" :id="player.id" :key="player.id" :color="player.color" :fieldLength="fieldLength" ref="monopolyPlayers"></MonopolyPlayer>


        <Dice :x="300-30" :y="300" ref="dice1"></Dice>
        <Dice :x="300+30" :y="300" ref="dice2"></Dice>
      </easel-canvas>
    </div>

    <div class="md-layout-item md-size-15">
      <h2>Aktionen</h2>

      <md-button v-for="req in possibleRequests" @click="req.method()">{{req.label}}</md-button>
    </div>
  </div>

  <div class="">
    {{info}}
    <h1>DEV TOOLS</h1>
    <md-button @click="__addFakePlayer()">add a fake player</md-button>
    <md-button @click='onPlayerMove({
      player_name: "pascal4",
      target: 11,
      type: "forward"})'>move</md-button>



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
      possibleRequests: [],
      canvas: {
        margin: 2
      },
      info: "Noch nichts passiert"
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
      "game_start": this.onGameStart,
      "possible_requests": this.onPossibleActions,
      "player_ready": this.onPlayerReady,
      "change_turn": this.onTurnChanged,
      "money_change": this.onMoneyChange,
      "roll_dice": this.onRollDice,
      "player_move": this.onPlayerMove,
      "error": (data) => {
        console.log(data);
      }
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
        let step = 2 * Math.PI / pCount;
        for (var i = 0; i < this.$refs.monopolyPlayers.length; i++) {
          this.$refs.monopolyPlayers[i].x = 2 + this.fieldLength / 2 + 25 * Math.sin((i + 1) * step);
          this.$refs.monopolyPlayers[i].y = 600 - 4 - this.fieldLength / 2 - 10 + 25 * Math.cos((i + 1) * step);
        }
      }

    },
    onPlayerMove: function(data) {
      //"data": {
      //  "player_name": "8080",
      //  "target": 11,
      //  "type": "forward"
      //}
      var player = _.find(this.players, (p) => p.nickname == data.player_name);
      var mps = [].concat(this.$refs.monopolyPlayers);
      var playerFigure = _.find(mps, (p) => p.id == player.id);
      player.currentField = data.target;
      var fs = this.$refs.fields;
      var field = _.find(fs, (f) => f.attributes.index == data.target)
      console.log(field);
      playerFigure.move(field.x, field.y);
    },
    onGameboard: function(data) {

      for (var i = 0; i < data.fields.length; i++) {
        data.fields[i].attributes = {
          color: this.colorMapping[data.fields[i].group],
          index: i
        };
      }
      var gameboard = data.fields;
      this.gameboard = data.fields;
      this.lane1 = [].concat(gameboard.slice(0, 10)).reverse();
      this.lane2 = gameboard.slice(10, 20);
      this.lane3 = gameboard.slice(20, 30);
      this.lane4 = [].concat(gameboard.slice(30, 40)).reverse();
      this.$store.commit("setGame", gameboard);
    },
    onGameStart: function() {
      this.info = "Los gehts!";
    },
    onPossibleActions: function(data) {

      let mapping = {
        "player_ready": {
          method: () => {
            this.gameConnection.setReady()
          },
          label: "Startklar"
        },
        "game_start": {
          method: () => {
            this.gameConnection.startGame()
          },
          label: "Spiel starten"
        },
        "roll_dice": {
          method: () => {
            this.gameConnection.send("roll_dice")
          },
          label: "Würfeln"
        },
        "buy_field": {
          method: () => {
            this.gameConnection.send("buy_field")
          },
          label: "Feld kaufen"
        },
        "end_turn": {
          method: () => {this.gameConnection.send("end_turn")},
          label: "Zug beenden"
        }
      };
      this.possibleRequests = [];
      console.log("Possible Requests", data.requests);
      for (var i = 0; i < data.requests.length; i++) {
        var r = {"method" : () => {this.gameConnection.send(data.requests[i].request)}, "label": data.requests[i].request}
        if (mapping.hasOwnProperty(data.requests[i].request)) {
          r.label = _.get(mapping, data.requests[i].request+'.label', r.label);
        }
        this.possibleRequests.push(mapping[data.requests[i].request])
      }
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
      this.info = data.player_name + " ist am Zug";
    },
    onMoneyChange: function(data) {
      console.log("Money change");
    },
    onRollDice: function(data) {
      this.info = data.player_name + " würfelt " + data.eyes[0] + ' und ' + data.eyes[1];
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
            "possible_requests": function() {
              this.rollDice();
            },
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
