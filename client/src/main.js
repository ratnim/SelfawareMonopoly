import Vue from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'
import './registerServiceWorker'
import VueMaterial from 'vue-material'
import 'vue-material/dist/vue-material.min.css'
import 'vue-material/dist/theme/default.css'
Vue.use(VueMaterial)

Vue.use(require('vue-easeljs'));

import VueWebsocket from "vue-websocket";
Vue.use(VueWebsocket, process.env.VUE_APP_WEBSOCKET_URL);

console.log("Websocket", process.env.VUE_APP_WEBSOCKET_URL);

Vue.config.productionTip = false

new Vue({
  router,
  store,
  render: h => h(App)
}).$mount('#app')
