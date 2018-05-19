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
    },
    twitter: {
      clientId: 'ZeIvP1jaKMjgUiQT65xSkMzt4',
      url: null,
      redirectUri: window.origin + '/auth/callback',
      responseType: 'token'
    },
    google: {
      clientId: '89280433713-ru4dkc7emg9oqlp3gaqejcqrf689vsqe.apps.googleusercontent.com',
      redirectUri: window.origin + '/auth/callback',
      responseType: 'token',
      scope: ['https://mail.google.com/']
    }
  }
})

export default new Vuex.Store({
  state: {
    nickname : '',
    isAuthenticated: false,
    tokens: {'instagram' : null, 'facebook' : null, 'google': null}
  },
  getters: {
    isAuthenticated() {
      return vueAuth.isAuthenticated()
    },
    getTokens(state) {
      return state.tokens
    },
    getNickname(state) {
      return state.nickname
    }
  },
  mutations: {
    isAuthenticated(state, payload) {
      state.isAuthenticated = payload.isAuthenticated
    },
    setToken(state, payload) {
      state.tokens[payload.provider] = payload.token
    },
    setNickname(state, payload) {
      state.nickname = payload
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
    },
    setNickname(context, nickname) {
      context.commit('setNickname', nickname);
    }
  }
})
