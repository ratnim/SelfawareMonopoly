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

<md-dialog :md-active.sync="show2" :md-click-outside-to-close="true">
    <md-dialog-title>Deine Chance:
        <br>{{title}}</md-dialog-title>
    <md-content class="content">
        <div class="" v-if="mode=='like'">
            <div class="md-layout">
                <div class="md-layout-item">
                    <img src="/img/monopolyman.jpg" alt="" style="height:160px">
                </div>
                <div class="md-layout-item">
                    <iframe src="https://www.facebook.com/plugins/like.php?href=https%3A%2F%2Fwww.facebook.com%2FHassoPlattnerInstitute%2F&width=450&layout=standard&action=like&size=small&show_faces=true&share=true&height=80&appId=206652186611333" width="450" height="80"
                    style="border:none;overflow:hidden" scrolling="no" frameborder="0" allowTransparency="true" allow="encrypted-media"></iframe>
                </div>
            </div>
        </div>



        <div v-if="mode=='sociallogin'">
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
                                    <md-option :value="i" v-for="i in [1,2,3,4,5,6]" :key="i">{{i}}</md-option>
                                </md-select>
                            </md-field>
                        </div>
                        <div class="md-layout-item">
                            <md-field style="width: 80px">
                                <label for="dice2">Würfel 2</label>
                                <md-select v-model="diceWish2" name="dice2" id="dice2" style="width: 80px">
                                    <md-option :value="i" v-for="i in [1,2,3,4,5,6]" :key="i">{{i}}</md-option>
                                </md-select>
                            </md-field>
                        </div>
                    </div>
                </div>
            </div>
            <div class="">
                <div>{{question}}</div>
                <md-button :disabled="dealReady" @click="authenticate(provider)">Klicke hier</md-button>
            </div>
        </div>




        <div v-if="mode == 'coinhive'">
            <div class="md-layout">
                <div class="md-layout-item">
                    <img src="/img/monopolyman.jpg" alt="" style="height:160px">
                </div>
                <div class="md-layout-item">
                    <p class="text">Gib uns etwas von deiner Rechenleistung, dafür sparst du beim nächsten Häuserbau Geld ein.</p>
                    <p class="text">Tipp: Stromkabel anschließen nicht vergessen.</p>
                </div>
            </div>
            <md-switch v-model="coinhive">Rechenleistung freigeben</md-switch>
        </div>

        <p>P.S. Die anderen erfahren nichts von diesem Trick.</p>
    </md-content>



    <md-dialog-actions>
        <!-- <md-button class="" @click="cancel">Deal abbrechen</md-button> -->
        <md-button v-if="mode == 'sociallogin'" class="md-primary" :disabled="((mode == 'sociallogin' && (!dealReady) || (diceWish1 == null) || (diceWish2 == null)))" @click="confirm">Deal abschließen</md-button>

        <md-button v-else class="md-primary" @click="confirm">Deal abschließen</md-button>
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
            show2: false,
            dealReady: false,
            fblikes: null,
            question: messages["generic"].question,
            title: messages["generic"].title,
            provider: "",
            mode: "sociallogin",
            coinhive: false,
        }
    },
    mounted() {
        var provider;
        if (this.tokens.facebook == null) {
            provider = "facebook";
        } else if (this.tokens.google == null) {
            provider = "google";
        } else {}
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
        open: function(mode) {
            this.mode = mode;
            if (this.mode == "coinhive") {
                this.title = "Sparen beim Bauen";
            } else if (this.mode == "like") {
                this.title = "Unterstütze uns und wir unterstützen Dich";
            }
            if (this.mode == "sociallogin") {
              var provider;
              if (this.tokens.facebook == null) {
                  provider = "facebook";
              } else if (this.tokens.google == null) {
                  provider = "google";
              } else {}
              this.provider = provider;
              if (messages[provider]) {
                  this.question = messages[provider].question;
                  this.title = messages[provider].title;
              }
            }
            console.log("mode:", this.mode);

            this.show2 = true;
        },
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
