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
  <md-field>
    <label for="nickname">Nickname</label>
    <md-input name="nickname" v-model="nickname" />
  </md-field>
  <md-button class="md-raised md-primary" :disabled="!nickname" @click="createAccount()">join</md-button>
</div>
</template>

<script>
import {
  mapGetters
} from 'vuex'

import * as homeConnection from '../storePlugins/homeConnection'


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
    homeConnection.connect();
    homeConnection.onJoinLobby(this.joinLobby);
    homeConnection.onError(this.error);
  },
  beforeRouteLeave(to, from, next) {
    homeConnection.disconnect();
    next();
  },

  methods: {
    authenticate: function(provider) {
      this.$store.dispatch('authenticate', {
        provider: provider
      })
    },
    createAccount: function() {
      homeConnection.createAccount(this.nickname);
      this.$store.dispatch('createAccount', this.nickname);
    },
    joinLobby: function(sessionId) {
      this.$router.push({ name: 'lobby', query: {session: sessionId}});
    },
    error: function(message) {
      console.log(message);
    }
  }
}
</script>
