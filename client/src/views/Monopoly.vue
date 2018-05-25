<template>
<div class="home">
  <h1>Monopoly</h1> Hi {{nickname}}
  <div class="">
    <md-button @click="rollDice()">ROLL THE DICE</md-button>
    <span>{{dice1}}, {{dice2}}</span>
    <md-button @click="move()">MOVE</md-button>
  </div>
  <div class="">
    <easel-canvas width="600" height="600" ref="stage">
      <!--from LOS to prison -->
      <MonopolyField v-for="(field, index) in game.fields[0].reverse()" :x="10" :y="10+fieldLength+index*fieldLength" :fieldWidth="fieldWidth" :fieldLength="fieldLength" :align="['bottom', 'left']" :label="field.label" :attributes="field.attributes"></MonopolyField>
      <!--from prison to free parking -->
      <MonopolyField v-for="(field, index) in game.fields[1]" :x="10+index*fieldLength" :y="10" :fieldWidth="fieldWidth" :fieldLength="fieldLength":label="field.label" :attributes="field.attributes"></MonopolyField>
      <!-- from free parking to goto prison -->
      <MonopolyField v-for="(field, index) in game.fields[2]" :x="600-10-fieldLength" :y="10+index*fieldLength" :fieldWidth="fieldWidth" :fieldLength="fieldLength" :align="['bottom', 'right']" :label="field.label" :attributes="field.attributes"></MonopolyField>
      <!-- from goto prision to los -->
      <MonopolyField v-for="(field, index) in game.fields[3].reverse()" :x="10+fieldLength+index*fieldLength" :y="600-10-fieldLength"  :fieldWidth="fieldWidth" :fieldLength="fieldLength" :label="field.label" :attributes="field.attributes"></MonopolyField>

      <!--the players -->
      <MonopolyPlayer color="yellow" :fieldLength="fieldLength" ref="player1"></MonopolyPlayer>
    </easel-canvas>
  </div>
</div>
</template>

<script>
import {
  mapGetters
} from 'vuex'


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
      player1 : {currentField : 0}
    }
  },
  computed: {
    ...mapGetters({
      'tokens': 'getTokens',
      'nickname': 'getNickname'
    })
  },
  mounted() {

  },
  methods: {
    rollDice : function() {
      this.dice1 = Math.floor(Math.random()*6)+1,
      this.dice2 = Math.floor(Math.random()*6)+1
    },
    move : function() {
      this.player1.currentField += this.dice1 + this.dice2
      this.$refs.player1.move(this.player1.currentField)
    }
  }
}
</script>
