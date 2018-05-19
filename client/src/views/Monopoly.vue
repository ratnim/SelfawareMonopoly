<template>
<div class="home">
  <h1>Monopoly</h1>
  Hi {{nickname}}
</div>
</template>

<script>
import {
  mapGetters
} from 'vuex'


export default {
  name: 'monopoly',
  computed: {
    ...mapGetters({
      'tokens': 'getTokens',
      'nickname': 'getNickname'
    })
  },
  methods: {
    authenticate: function(provider) {
      this.$store.dispatch('authenticate', {
        provider: provider
      })
    }
  }
}
</script>
