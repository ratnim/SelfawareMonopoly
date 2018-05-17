import Vue from 'vue'
import Router from 'vue-router'
import Home from './views/Home.vue'
import Callback from './views/Callback.vue'

Vue.use(Router)

export default new Router({
  mode: 'history',
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
    }
  ]
})
