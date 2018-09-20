<style scoped>

.content {
    padding: 20px;
}

.text {
    font-size: 20px;
    line-height: 1.5;
}

.md-menu-content.md-select-menu {
  width: auto;
}

</style>

<template>

<md-dialog :md-active.sync="show2" :md-click-outside-to-close="false">
    <md-dialog-title>Deine Chance: <br>{{title}}</md-dialog-title>
    <md-content class="content">
        <div class="md-layout">
            <div class="md-layout-item">
                <img src="/img/monopolyman.jpg" alt="" style="height:160px"></div>
            <div class="md-layout-item">
                <p class="text">Was willst du als nächstes würfeln?</p>
                <div class="md-layout">
                    <div class="md-layout-item">
                        <md-field style="width: 80px">
                            <label for="dice1">Würfel 1</label>
                            <md-select v-model="diceWish1" name="dice1" id="dice1" style="width: 80px">
                                <md-option :value="i" v-for="i in [1,2,3,4,5,6]">{{i}}</md-option>
                            </md-select>
                        </md-field>
                    </div>
                    <div class="md-layout-item">
                        <md-field style="width: 80px">
                            <label for="dice2">Würfel 2</label>
                            <md-select v-model="diceWish2" name="dice2" id="dice2" style="width: 80px">
                                <md-option :value="i" v-for="i in [1,2,3,4,5,6]">{{i}}</md-option>
                            </md-select>
                        </md-field>
                    </div>
                </div>
            </div>
        </div>
        <div class="">
            <div>{{question}}</div>
            <md-button @click="authenticate(provider)">Klicke hier</md-button>
        </div>

        <p>P.S. Die anderen erfahren nichts von diesem Trick.</p>
    </md-content>

    <!-- <iframe src="https://www.facebook.com/plugins/like.php?href=https%3A%2F%2Fzdf.de&width=450&layout=standard&action=like&size=large&show_faces=true&share=true&height=80&appId=1720802108194706" width="450" height="80" style="border:none;overflow:hidden" scrolling="no" frameborder="0" allowTransparency="true" allow="encrypted-media"></iframe> -->

    <md-dialog-actions>
        <md-button class="" @click="cancel">Deal abbrechen</md-button>
        <md-button class="md-primary" :disabled="(!dealReady) || (diceWish1 == null) || (diceWish2 == null)" @click="confirm">Deal abschließen</md-button>
    </md-dialog-actions>
</md-dialog>

</template>

<script>

import {
    mapGetters
}
from 'vuex'

var messages = {
  "generic": {
      "title": "Kontrolliere die Würfel",
      "question": "Erlaube mir etwas von Dir zu erfahren: "
  },
    "facebook": {
        "title": "Nutzername gegen Wunschergebnis",
        "question": "Erlaube mir Deinen Nutzernamen zu erfahren: "
    }
};

export default {
    name: 'WatsonDialog',
    props: {
        show: Boolean,
        mode: "sociallogin",
        onYes: Function,
        onNo: Function
    },
    computed: {
        ...mapGetters({
                'tokens': 'getTokens'
            }),
            dealReady2: () => this.fblikes != null && this.diceWish1 != null && this.diceWish2 != null,
          //  title: () => {console.log(this.provider); return messages[this.provider] != null ? messages[this.provider]["title"] : messages["generic"]["title"]},
      //      question: () => { return messages[this.provider] != null ? messages[this.provider]["question"] : messages["generic"]["question"]},
    },
    data: function() {
        return {
            diceWish1: null,
            diceWish2: null,
            show2: true,
            dealReady: false,
            fblikes: null,
            question: messages["generic"].question,
            title: messages["generic"].title,
            provider: ""
        }
    },
    mounted() {
      var provider;
      if (this.tokens.facebook == null) {
        provider = "facebook";
      } else if (this.tokens.google == null) {
        provider = "google";
      } else {
      }
      this.provider = provider;
      if (messages[provider]) {
        this.question = messages[provider].question;
        this.title = messages[provider].title;
      }
        this.$store.watch(
                (state) => {
                    return this.$store.state.tokens // could also put a Getter here
                }, (oldTokens, newTokens) => {
                    if (newTokens[this.provider]) {
                        this.dealReady = true;

                    }
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
            //if (this.tokens["facebook"]) {
            //    this.getFacebookLikes();
            //}
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
            }).then((resp) => {
                console.log(resp);
                this.fblikes = resp.data;
                this.dealReady = true;
                vm.dealReady = true;

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
