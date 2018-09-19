

<template>

<md-dialog :md-active.sync="show2">
    <md-dialog-title>Hi</md-dialog-title>
    <p>Was willst du würfeln?</p>
    <md-field>
        <label for="dice">Würfel</label>
        <md-select v-model="diceWish" name="dice" id="dice">
            <md-option :value="i" v-for="i in [2,3,4,5,6,7,8,9,10,11,12]">{{i}}</md-option>
        </md-select>
    </md-field>
    <p>P.S. Die anderen erfahren nichts, von diesem Trick.</p>
    <md-button @click="authenticate(provider)">Login with {{provider}}</md-button>


    <!-- <iframe src="https://www.facebook.com/plugins/like.php?href=https%3A%2F%2Fzdf.de&width=450&layout=standard&action=like&size=large&show_faces=true&share=true&height=80&appId=1720802108194706" width="450" height="80" style="border:none;overflow:hidden" scrolling="no" frameborder="0" allowTransparency="true" allow="encrypted-media"></iframe> -->

    <md-dialog-actions>
        <md-button class="md-primary" @click="show2 = false">Abbrechen</md-button>
        <!-- <md-button class="md-primary" @click="show2 = false">Save</md-button> -->
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
        mode: "sociallogin"
            //onYes: Function,
            //onNo: Function
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
            show2: true
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

            }).catch(function(err) {
                console.log("Error");
                console.log(err);
            });

        }
    }
}

</script>
