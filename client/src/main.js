//Basic Setunp
import Vue from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'
import './registerServiceWorker'

//Material Design
import VueMaterial from 'vue-material'
import 'vue-material/dist/vue-material.min.css'
import 'vue-material/dist/theme/default.css'
Vue.use(VueMaterial)

//EaselJS (Drawing on Canvas)
Vue.use(require('vue-easeljs'));

//Websocket Communication
//import VueWebsocket from "vue-websocket";
//Vue.use(VueWebsocket,process.env.VUE_APP_WEBSOCKET_URL);
//console.log("Websocket", process.env.VUE_APP_WEBSOCKET_URL);

import axios from 'axios'
import VueAxios from 'vue-axios'

Vue.use(VueAxios, axios)

Vue.config.productionTip = false

new Vue({
  router,
  store,
  render: h => h(App)
}).$mount('#app')
