<template>
<div class="home">
<h1>GO TO /lobby !!!</h1>
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

import * as homeConnection from '../sockets/homeConnection'


export default {
  name: 'home',
  data: function() {
    return {
      nickname: ''
    }
  },
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

  created() {
    //homeConnection.connect();
    //homeConnection.onJoinLobby(this.onJoinLobby);
    //homeConnection.onError(this.onError);
  },
  beforeRouteLeave(to, from, next) {
    //homeConnection.disconnect();
    next();
  },

  methods: {
    authenticate: function(provider) {
      this.$store.dispatch('authenticate', {
        provider: provider
      })
    },
    createAccount: function() {
      //homeConnection.createAccount(this.nickname);
      this.$store.dispatch('createAccount', this.nickname);
    },
    onJoinLobby: function(sessionId) {
      this.$router.push({ name: 'lobby' });
      //this.$store.commit('setSessionId', sessionId);
    },
    onError: function(message) {
      console.log(message);
    }
  }
}
</script>
