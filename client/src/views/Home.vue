<template>
<div class="home">
  <h1>The more we get, the more you get</h1>
  <div v-for="(token, provider) in tokens">
    <button @click="authenticate(provider)" v-bind:disabled="tokens[provider]">Login with {{provider}}</button>
  </div>
  <h2>Token Overview</h2>
  <div v-for="(token, provider) in tokens" v-show="token">
    {{provider}} : {{token}}
  </div>
</div>
</template>

<script>
import {
  mapGetters
} from 'vuex'


export default {
  name: 'home',
  computed: {
    ...mapGetters({
      'tokens': 'getTokens'
    })
  },
  watch: {
    tokens(newv, oldv) {
      console.log("instagram token changed")
    }
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
