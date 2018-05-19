import Vue from 'vue'
import Router from 'vue-router'
import Home from './views/Home.vue'
import Callback from './views/Callback.vue'
import Lobby from './views/Lobby.vue'
import Monopoly from './views/Monopoly.vue'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/',
      name: 'home',
      component: Home
    },
    {
      path: '/auth/callback',
      name: 'callback',
      component: Callback
    },
    {
      path: '/lobby',
      name: 'lobby',
      component: Lobby
    },
    {
      path: '/monopoly/:gameid',
      name: 'monopoly',
      component: Monopoly
    }
  ]
})
