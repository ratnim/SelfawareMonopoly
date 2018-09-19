

<template>

<md-dialog :md-active.sync="show2">
    <md-dialog-title>Deine Chance: Nutzername gegen Wunschergebnis</md-dialog-title>
    <div class="">
      <p>Was willst du als nächstes würfeln?</p>
      <md-field style="width: 200px">
          <label for="dice">Würfel</label>
          <md-select v-model="diceWish" name="dice" id="dice">
              <md-option :value="i" v-for="i in [2,3,4,5,6,7,8,9,10,11,12]">{{i}}</md-option>
          </md-select>
      </md-field>
      <md-button @click="authenticate(provider)">Klicke hier und du wirst zu facebook weitergeleitet</md-button>
      <p>P.S. Die anderen erfahren nichts, von diesem Trick.</p>
    </div>

    <!-- <iframe src="https://www.facebook.com/plugins/like.php?href=https%3A%2F%2Fzdf.de&width=450&layout=standard&action=like&size=large&show_faces=true&share=true&height=80&appId=1720802108194706" width="450" height="80" style="border:none;overflow:hidden" scrolling="no" frameborder="0" allowTransparency="true" allow="encrypted-media"></iframe> -->

    <md-dialog-actions>
        <md-button class="" @click="cancel">Deal abbrechen</md-button>
        <md-button class="md-primary" :disabled="!dealRaedy" @click="confirm">Deal abschließen</md-button>
    </md-dialog-actions>
</md-dialog>

</template>

<script>

import {
    mapGetters
}
from 'vuex'


export default {
    name: 'WatsonDialog',
    props: {
        show: Boolean,
        question: {
            type: String,
            default: "Willst Du dir deine Spielerfarbe aussuchen?"
        },
        mode: "sociallogin",
        onYes: Function,
        onNo: Function
    },
    computed: {
        ...mapGetters({
            'tokens': 'getTokens'
        })
    },
    data: function() {
        return {
            diceWish: null,
            provider: "facebook",
            show2: true,
            dealRaedy: false
        }
    },
    mounted() {
      if (this.tokens["facebook"]) {
        this.getFacebookLikes();
      }
    },
    watch: {
        // whenever tokens changes, this function will run
        tokens: function(oldTokens, newTokens) {
            if (newTokens["facebook"]) {
                this.getFacebookLikes();
            }
        }
    },
    methods: {
        authenticate: function(provider) {
            this.$store.dispatch('authenticate', {
                provider: provider
            })
        },
        getFacebookLikes: function() {
          let vm = this;
            let url = "https://graph.facebook.com/v3.1/me/likes?limit=100";
            this.axios({
                method: 'get',
                url: url,
                //params: {'HTTP_CONTENT_LANGUAGE': self.language},
                headers: {
                    'Authorization': 'Bearer ' + this.tokens['facebook']
                }
            }).then(function(resp) {
                console.log(resp);
                vm.fblikes = resp.data;
                vm.dealRaedy = true;

            }).catch(function(err) {
                console.log("Error");
                console.log(err);
            });

        },
        cancel: function() {
          this.show2 = false;
          this.onNo();
        },
        confirm: function() {
          this.show2 = false;
          this.onYes();
        }
    }
}

</script>
