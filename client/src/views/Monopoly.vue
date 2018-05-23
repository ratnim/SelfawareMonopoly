<template>
<div class="home">
  <h1>Monopoly</h1> Hi {{nickname}}
  <div class="">
    <easel-canvas width="600" height="600">
      <!--from LOS to prison -->
      <MonopolyField v-for="(field, index) in game.fields[0].reverse()" :x="10" :y="10+fieldLength+index*fieldLength" :fieldWidth="fieldWidth" :fieldLength="fieldLength" :align="['bottom', 'left']" :label="field.label" :attributes="field.attributes"></MonopolyField>
      <!--from prison to free parking -->
      <MonopolyField v-for="(field, index) in game.fields[1]" :x="10+index*fieldLength" :y="10" :fieldWidth="fieldWidth" :fieldLength="fieldLength":label="field.label" :attributes="field.attributes"></MonopolyField>
      <!-- from free parking to goto prison -->
      <MonopolyField v-for="(field, index) in game.fields[2]" :x="600-10-fieldLength" :y="10+index*fieldLength" :fieldWidth="fieldWidth" :fieldLength="fieldLength" :align="['bottom', 'right']" :label="field.label" :attributes="field.attributes"></MonopolyField>
      <!-- from goto prision to los -->
      <MonopolyField v-for="(field, index) in game.fields[3].reverse()" :x="10+fieldLength+index*fieldLength" :y="600-10-fieldLength"  :fieldWidth="fieldWidth" :fieldLength="fieldLength" :label="field.label" :attributes="field.attributes"></MonopolyField>

    </easel-canvas>
  </div>
</div>
</template>

<script>
import {
  mapGetters
} from 'vuex'

import MonopolyField from '@/components/MonopolyField'

import game from '@/assets/game.json'

export default {
  name: 'monopoly',
  components: {
    MonopolyField
  },
  data: function() {
    return {
      fieldWidth: (600-10-10)/4,
      fieldLength: (600-10-10)/4,
      game: game
    }
  },
  computed: {
    ...mapGetters({
      'tokens': 'getTokens',
      'nickname': 'getNickname'
    })
  },
  methods: {
    authenticate: function(provider) {
      this.$store.dispatch('authenticate', {
        provider: provider
      })
    }
  }
}
</script>
