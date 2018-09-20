

<template>

<md-dialog :md-active.sync="show2">
    <md-dialog-title>Deine Chance: Nutzername gegen Wunschergebnis</md-dialog-title>
    <div class="">
        <p>Was willst du als nächstes würfeln?</p>
        <md-field style="width: 100px">
            <label for="dice1">Würfel 1</label>
            <md-select v-model="diceWish1" name="dice1" id="dice1">
                <md-option :value="i" v-for="i in [1,2,3,4,5,6]">{{i}}</md-option>
            </md-select>
        </md-field>
        <md-field style="width: 100px">
            <label for="dice2">Würfel 2</label>
            <md-select v-model="diceWish2" name="dice2" id="dice2">
                <md-option :value="i" v-for="i in [1,2,3,4,5,6]">{{i}}</md-option>
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
            diceWish1: null,
            diceWish2: null,
            provider: "facebook",
            show2: true,
            dealRaedy: false
        }
    },
    mounted() {
        this.$store.watch(
            (state) => {
                return this.$store.state.tokens // could also put a Getter here
            }, (newTokens, oldValue) => {
                if (newTokens["facebook"]) {
                    console.log("watch success");
                    this.getFacebookLikes();
                }
            },
            //Optional Deep if you need it
            {
                deep: true
            }
        )
        if (this.tokens["facebook"]) {
            this.getFacebookLikes();
        }
    },
    watch: {},
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
            this.onYes({
                dices: [this.diceWish1, this.diceWish2]
            });
        }
    }
}

</script>
