import Vue from 'vue'
import Lifegame from './Lifegame.vue'

Vue.config.productionTip = false

new Vue({
  render: h => h(Lifegame),
}).$mount('#lifegame')
