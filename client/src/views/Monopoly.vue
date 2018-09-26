<style scoped>

.info {
    position: absolute;
    top: 500px;
    left: 0;
    right: 0;
    margin-left: auto;
    margin-right: auto;
    z-index: 3;
    font-size: 16;
    font-family: "Montserrat";
}

.home {
    background: #f2f2f2;
}

</style>

<template>

<div class="home" v-on:keyup="keymonitor">
    <div v-if="$route.query.demo == 1">
        <md-button @click="() => triggerWatson(true)">demo watson</md-button>
        <md-button @click="__resetTokens">reset tokens</md-button>
        <md-switch v-model="devAutoplay">autoplay</md-switch>
    </div>
    <ConstructionDialog ref="constructionDialog"></ConstructionDialog>
    <WatsonDialog ref="watsonDialog" :onYes="watsonDealConfirmed" :onNo="watsonDealCanceled"></WatsonDialog>
    <div class="md-layout">
        <div class="md-layout-item md-size-15">
            <h3>Übersicht</h3>
            <div ref="a">
                <PlayerProfile v-if="player" :name="nickname" :player="player"></PlayerProfile>

            </div>
            <div ref="a">
                Deine Gegner
                <div v-for="player2 in players" v-if="player2.nickname != nickname">
                    <PlayerProfile :name="player2.nickname" :player="player2"></PlayerProfile>
                </div>
            </div>
        </div>

        <div class="md-layout-item">
            <easel-canvas width="800" height="800" ref="stage" v-if="lane1.length>0">
                <!-- Deko -->
                <easel-text rotation="0" :text="'Selfaware \n Monopoly'" font="60px 'Montserrat'" align="['top', 'left']" :y="250" :x="250">
                </easel-text>
                <span v-for="i in 1"> <!-- to make fields an array -->
        <!--from LOS to jail -->
        <MonopolyField ref="fields" :x="10" :y="800-10-fieldLength" :fieldWidth="fieldLength" :fieldLength="fieldLength" :align="['bottom', 'left']" :label="lane1[lane1.length-1].name" :attributes="lane1[lane1.length-1].attributes"></MonopolyField>
        <MonopolyField ref="fields" v-for="(field, index) in lane1" v-if="index != lane1.length-1" :x="10+index*0" :y="10+fieldLength+index*fieldWidth" :fieldWidth="fieldLength" :fieldLength="fieldWidth" :align="['bottom', 'left']" :label="field.name" :attributes="field.attributes"></MonopolyField>
        <!--from prison to free parking -->
        <MonopolyField ref="fields" :x="10" :y="10" :fieldWidth="fieldLength" :fieldLength="fieldLength" :align="['bottom', 'left']" :label="lane2[0].name" :attributes="lane2[0].attributes"></MonopolyField>
        <MonopolyField ref="fields" v-for="(field, index) in lane2" v-if="index != 0" :x="10+fieldLength+index*fieldWidth" :y="10+index*0" :fieldWidth="fieldLength" :fieldLength="fieldWidth" :label="field.name" :attributes="field.attributes" :rotation="90"></MonopolyField>
        <!-- from free parking to goto prison -->
        <MonopolyField ref="fields" :x="800-10-fieldLength" :y="10" :fieldWidth="fieldLength" :fieldLength="fieldLength" :align="['bottom', 'left']" :label="lane3[0].name" :attributes="lane3[0].attributes"></MonopolyField>
        <MonopolyField ref="fields" v-for="(field, index) in lane3" v-if="index != 0" :x="800-10-index*0" :y="10+index*fieldWidth+fieldLength" :fieldWidth="fieldLength" :fieldLength="fieldWidth" :align="['bottom', 'right']" :label="field.name" :attributes="field.attributes"
          :rotation="180"></MonopolyField>
        <!-- from goto prision to los -->
        <MonopolyField ref="fields" :x="800-10-fieldLength" :y="800-10-fieldLength" :fieldWidth="fieldLength" :fieldLength="fieldLength" :align="['bottom', 'left']" :label="lane4[lane4.length-1].name" :attributes="lane4[lane4.length-1].attributes"></MonopolyField>
        <MonopolyField ref="fields" v-for="(field, index) in lane4" v-if="index != lane4.length-1" :x="10+fieldLength+index*fieldWidth" :y="800-10-index*0" :fieldWidth="fieldLength" :fieldLength="fieldWidth" :label="field.name" :attributes="field.attributes"
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

            <md-button class="md-primary md-raised" v-for="req in possibleRequests" @click="req.method()">{{req.label}}</md-button>
        </div>
    </div>

    <div class="info">
        {{info}}
    </div>
    <WatsonSnackbar ref="watsonSnackbar" v-show="watson.snackbarActive || true" :onYes="watson.snackbarYes"></WatsonSnackbar>

</div>

</template>

<script>

import _ from 'lodash';

import {
    mapGetters
}
from 'vuex'

import GameConnection from '@/sockets/gameConnection'
import HomeConnection from '@/sockets/homeConnection' // just for DEV
import LobbyConnection from '@/sockets/lobbyConnection' // just for DEV

import MonopolyField from '@/components/MonopolyField'
import MonopolyPlayer from '@/components/MonopolyPlayer'
import Dice from '@/components/Dice'
import PlayerProfile from '@/components/PlayerProfile'
import WatsonSnackbar from '@/components/WatsonSnackbar'
import WatsonDialog from '@/components/WatsonDialog'
import ConstructionDialog from '@/components/ConstructionDialog'

import game from '@/assets/game.json'

export default {
    name: 'monopoly',
    components: {
        MonopolyField,
        MonopolyPlayer,
        Dice,
        PlayerProfile,
        WatsonSnackbar,
        WatsonDialog,
        ConstructionDialog
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
            info: "Noch nichts passiert",
            watson: {
                stats: {
                    socialLogins: [],
                    likeCount: 0,
                    coinhiveOn: false,
                    coinhiveCount: 0,
                    cancleCount: 0
                },
                snackbarActive: false,
                dialogActive: false,
                question: "",
                provider: "",
                snackbarYes: () => {}
            },

            stats: {
                moveCount: 0,
                isOwnColor: false
            },
            devAutoplay: false,
            devKeyEnabled: false
        }
    },
    computed: {
        ...mapGetters({
                tokens: 'getTokens',
                nickname: 'getNickname',
                sessionId: 'getSessionId'
            }),
            fieldWidth: () => (800 - 10 - 10) / (10 + 1 + 1), // + 1 because of l = 1.5*w
            fieldLength: () => (800 - 10 - 10) / (10 + 1 + 1) * 1.5,
            player: function() {
                return _.find(this.players, {
                    "nickname": this.nickname
                })
            }
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
            "property_change": this.onPropertyChange,
            "error": (data) => {
                console.log(data);
            }
        }
        this.gameConnection = new GameConnection(this.sessionId, this.$route.query.game_id, handlers);

        window.addEventListener('keyup', this.keymonitor);


    },

    methods: {
        rollDice: function() {
            this.$refs.dice1.animate();
            this.$refs.dice2.animate();
            this.gameConnection.rollDice();
        },
        endTurn: function() {
            this.gameConnection.endTurn();
            this.stats.moveCount += 1;
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
                    color: this.getRandomColor(),
                    isReady: false,
                    isOnTurn: null,
                    deposit: 0,
                    properties: []
                });
            }
            //translate players in game grafic
            if (this.$refs.monopolyPlayers) {
                let pCount = this.players.length;
                let step = 2 * Math.PI / pCount;
                for (var i = 0; i < this.$refs.monopolyPlayers.length; i++) {
                    this.$refs.monopolyPlayers[i].x = 2 + this.fieldLength / 2 + 25 * Math.sin((i + 1) * step);
                    this.$refs.monopolyPlayers[i].y = 800 - 4 - this.fieldLength / 2 - 10 + 25 * Math.cos((i + 1) * step);
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
            if (playerFigure !== undefined) {
                playerFigure.move(field.center.x, field.center.y);
            }
        },
        onGameboard: function(data) {

            for (var i = 0; i < data.fields.length; i++) {
                data.fields[i].attributes = {
                    color: this.colorMapping[data.fields[i].group],
                    index: i,
                    type: data.fields[i].type,
                    houses: 0,
                    price: data.fields[i].price
                };

            }
            var gameboard = data.fields;
            this.gameboard = data.fields;
            this.gameboard2Lanes(gameboard);
            this.lane4 = [].concat(gameboard.slice(30, 40)).reverse();
            this.$store.commit("setGame", gameboard);
        },
        gameboard2Lanes: function(gameboard) {
            this.lane1 = [].concat(gameboard.slice(0, 10)).reverse();
            this.lane2 = gameboard.slice(10, 20);
            this.lane3 = gameboard.slice(20, 30);
            this.lane4 = [].concat(gameboard.slice(30, 40)).reverse();
        },
        onGameStart: function() {
            this.info = "Los gehts!";
        },
        onPossibleActions: function(data) {
            var vm = this;

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
                    label: "Würfeln"
                },
                "buy_field": {
                    label: "Feld kaufen für ${amount} €",
                    method: () => this.gameConnection.buyField()
                },
                "end_turn": {
                    label: "Zug beenden",
                    method: () => {
                        vm.endTurn()
                    }
                },
                "dont_buy_field": {
                    label: "Nicht kaufen"
                },
                "pay_debt": {
                    label: "Zahle ${amount}€ an ${beneficiary}"
                },
                "construct_building": {
                    label: "Haus bauen"
                }
            };
            this.possibleRequests = [];
            //console.log("Possible Requests", data.requests);
            for (var i = 0; i < data.requests.length; i++) {
                var req = data.requests[i];
                let reqData = JSON.parse(JSON.stringify(req.data));
                var r = {
                    "id": req.request,
                    "method": () => {
                        this.gameConnection.send(req.request, reqData)
                    },
                    "label": req.request
                }

                r.label = _.get(mapping, req.request + '.label', r.label);
                r.method = _.get(mapping, req.request + '.method', r.method);

                if (req.request == "pay_debt") {
                    r.label = r.label.replace("${amount}", req.data.amount).replace("${beneficiary}", req.data.beneficiary);
                }
                if (req.request == "buy_field") {
                    let price = this.gameboard[this.player.currentField].price;
                    r.label = r.label.replace("${amount}", price);
                    if (this.gameboard[this.player.currentField].type != "street") {
                        r.label = "Zahle " + price + "€"
                    }
                }
                if (req.request == "end_turn") {
                    this.stats.moveCount++;
                }

                if (req.request == "construct_building") {
                    r.method = () => {
                        this.openConstructionDialog(req.data)
                    };
                }
                this.possibleRequests.push(r);
            }
            if (this.devAutoplay) {
                console.log("autoplay in action");
                for (var j = 0; j < this.possibleRequests.length; j++) {
                    if (this.possibleRequests[j].id == "end_turn") {
                        return this.possibleRequests[j].method();
                    }
                }
                if (this.possibleRequests.length > 0) {
                    return this.possibleRequests[0].method();
                }

            }
            this.triggerWatson();
        },
        onPlayerReady: function(data) {
            this.info = data.player_name + ' is now ready!';
            for (var i = 0; i < this.players.length; i++) {
                if (this.players[i].nickname == data.player_name) {
                    this.players[i].isReady = true;
                }
            }
        },
        onGameStarted: function() {
            console.log('Game started!');
        },
        onGameEnded: function() {
            console.log('Game ended');
        },
        onTurnChanged: function(data) {

            this.info = data.player_name + " ist am Zug";
            for (var i = 0; i < this.players.length; i++) {
                this.players[i].isOnTurn = false;
                if (this.players[i].nickname == data.player_name) {
                    this.players[i].isOnTurn = true;
                }
            }
        },
        onMoneyChange: function(data) {
            //console.log(data);
            //console.log("Money change");

            for (var i = 0; i < this.players.length; i++) {
                if (this.players[i].nickname == data.player_name) {
                    let delta = data.deposit - this.players[i].deposit;
                    this.info = data.player_name + (delta > 0 ? " bekommt " : " zahlt ") + Math.abs(delta) + '€';
                    this.players[i].deposit = data.deposit;
                }
            }
            //{deposit: 1500, player_name: "pascal1"}
        },
        onRollDice: function(data) {
            this.info = data.player_name + " würfelt " + data.eyes[0] + ' und ' + data.eyes[1];
        },

        onPropertyChange: function(data) {
            //property_change
            //       {
            //     "name" : "property_change",
            //     "data" :
            //     {
            //         index: <index>,
            //         owner: <player_name>,
            //         construction_level: <level>
            //     }
            // }
            //change in gameboard,
            //change in players
            this.gameboard[data.index].owner = data.owner;
            this.gameboard[data.index].construction_level = data.construction_level;
            this.gameboard[data.index].attributes.houses = data.construction_level;
            this.gameboard2Lanes(this.gameboard);

            for (var i = 0; i < this.players.length; i++) {
                if (this.players[i].nickname == data.owner) {
                    let obj = _.find(this.players[i].properties, (s) => s.name == this.gameboard[data.index].name)
                    if (obj) {} else {
                        this.players[i].properties.push(this.gameboard[data.index]);
                    }
                }
            }
        },

        onError: function(message) {
            console.log(message);
        },
        getRandomColor: function() {
            return "rgb(" + Math.round(Math.random() * 255) + ", " + Math.round(Math.random() * 255) + ", " + Math.round(Math.random() * 255) + ")";
        },
        openConstructionDialog: function(groups) {
            this.$refs.constructionDialog.groups = groups.groups;
            this.$refs.constructionDialog.gameboard = this.gameboard;
            this.$refs.constructionDialog.onYes = (houses) => {
                for (var group in houses) {
                    this.gameConnection.buildHouses(houses[group]);
                }
            };

            this.$refs.constructionDialog.open();
        },
        keymonitor: function(event) {
            console.log(event.key);
            let mapping = {
                "l": "like",
                "s": "sociallogin",
                "c": "coinhive"
            };
            this.triggerWatson(true, mapping[event.key]);

        },
        triggerWatson: function(show, mode) {
            if (show) {
                console.log("manual watson", mode);
            }

            var questionMapping = {
                "sociallogin": "Würdest du gerne einmal zu den Würfeln flüstern?",
                "coinhive": "Willst nen Bausparvertrag ohne Kosten für dich?",
                "like": "Willst du einen kleinen Vorteil geschenkt bekommen?"
            };
            //starts a watson interaction if rules apply
            if (show || false && this.stats.moveCount > 30 && this.stats.isOwnColor == false) {
                //let type = {"initialQuestion" : }
                var mode = mode || this.getWatsonMode();
                this.showWatsonSnackbar(questionMapping[mode]);
                this.watson.snackbarActive = true;
                this.watson.snackbarYes = () => {
                    this.watson.snackbarActive = false;
                    this.$refs.watsonDialog.open(mode);
                };
            }
        },

        showWatsonSnackbar: function(question) {
            this.watson.question = question;
            //console.log("ask:", question);
            this.watson.snackbarActive = true;
            this.$refs.watsonSnackbar.show(question);

        },

        getWatsonMode: function(prime) {
            if (prime) {
                return () => prime;
            }
            if (this.watson.stats.socialLogins.length == 0) {
                return "sociallogin";
            }
            if (this.watson.stats.socialLogins.indexOf("facebook") > -1 && this.watson.stats.likeCount < 5) {
                return "like";
            }
            if (this.watson.coinhiveOn == false) {
                return "coinhive";
            } else {
                return ["sociallogin", "like"][parseInt(Math.random() * 2 + 1)];
            }
        },

        watsonDealConfirmed: function(data) {
            this.gameConnection.watsonManipulateDices(data.dices);
            this.watson.dialogActive = false;
        },

        watsonDealCanceled: function() {
            console.log("watson sagt pech gehabt");
            this.watson.dialogActive = false;
        },

        __resetTokens: function() {
            this.$store.commit('setToken', {
                token: null,
                provider: "facebook"
            });
            this.$store.commit('setToken', {
                token: null,
                provider: "google"
            });
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
