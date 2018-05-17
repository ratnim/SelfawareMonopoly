import Vue from 'vue'
import Vuex from 'vuex'
//import vueAuth from './auth'
import VueAxios from 'vue-axios'
import {
  VueAuthenticate
} from 'vue-authenticate'
import axios from 'axios';

Vue.use(Vuex)

Vue.use(VueAxios, axios)

const vueAuth = new VueAuthenticate(Vue.prototype.$http, {
  baseUrl: window.origin,
  providers: {
    instagram: {
      clientId: '3a821ea9be0d41018cd34d750b069910',
      redirectUri: window.origin + '/auth/callback',
      url: null,
      tokenName: 'instagram_token',
      responseType: 'token'
    },
    linkedin: {
      clientId: '86quhw3wxqcgr9',
      redirectUri: 'http://localhost:8080/auth/callback',
      responseType: 'code'
    },
    facebook: {
      clientId: '1720802108194706',
      redirectUri: window.origin + '/auth/callback',
      responseType: 'token'
    }
  }
})

export default new Vuex.Store({
  state: {
    isAuthenticated: false,
    tokens: {'instagram' : null, 'facebook' : null}
  },
  getters: {
    isAuthenticated() {
      return vueAuth.isAuthenticated()
    },
    getTokens(state) {
      return state.tokens
    }
  },
  mutations: {
    isAuthenticated(state, payload) {
      state.isAuthenticated = payload.isAuthenticated
    },
    setToken(state, payload) {
      state.tokens[payload.provider] = payload.token
    }
  },
  actions: {
    // Perform VueAuthenticate login using Vuex actions
    login(context, payload) {

      vueAuth.login(payload.user, payload.requestOptions).then((response) => {
        context.commit('isAuthenticated', {
          isAuthenticated: vueAuth.isAuthenticated()
        })
      })
    },
    authenticate(context, payload) {
      console.log('authenticate ', payload.provider);
      vueAuth.authenticate(payload.provider).then(function(response) {
        console.log("authenticated", response)
        context.commit('setToken', {
          token: response.access_token,
          provider: payload.provider
        })
      })
    }
  }
})
