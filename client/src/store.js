import Vue from 'vue'
import Vuex from 'vuex'
Vue.use(Vuex)

//OAuth
import VueAxios from 'vue-axios'
import { VueAuthenticate } from 'vue-authenticate'
import axios from 'axios';
Vue.use(VueAxios, axios)

//Plugin to persist state in local storage
import VuexPersist from 'vuex-persist';

const vuexLocalStorage = new VuexPersist({
  key: 'vuex', // The key to store the state on in the storage provider.
  storage: window.localStorage, // or window.sessionStorage or localForage
  // Function that passes the state and returns the state with only the objects you want to store.
  // reducer: state => state,
  // Function that passes a mutation and lets you decide if it should update the state in localStorage.
  // filter: mutation => (true)
})


//TODO should be moved to ./auth
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
  plugins: [vuexLocalStorage.plugin],
  state: {
    sessionId: '',
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
    },
    getSessionId(state) {
      return state.sessionId;
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
    },
    setSessionId(state, payload) {
      state.sessionId = payload;
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
    createAccount(context, nickname) {
      context.commit('setNickname', nickname);
    },
  }
})
