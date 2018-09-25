<style scoped>

.content {
    padding: 20px;
}

.text {
    font-size: 20px;
    line-height: 1.5;
}

</style>

<template>

<md-dialog :md-active.sync="show2" :md-click-outside-to-close="true">
    <md-dialog-title>Hausbau</md-dialog-title>
    <md-content class="content">
      <div v-for="street in streets">

        <div class="md-layout">
            <div class="md-layout-item">
                <span>{{street.name}}</span>
            </div>
            <div class="md-layout-item">
                <span v-if="construction[street.name] < 5" v-for="h in construction[street.name]"><img src="/img/icons/house2.png" style="height:30px" alt="X"></span>
                <span v-if="construction[street.name] == 5"><img src="/img/icons/hotel1.png" style="height:30px" alt="XXXXX"></span>
            </div>
        </div>
        <div class="">
            <md-button :disabled="!street.showMinus" @click="() => construct(street.name, -1)">-</md-button>
            <md-button :disabled="!street.showPlus" @click="() => construct(street.name, +1)">+</md-button>
        </div>

      </div>

    </md-content>

    <md-dialog-actions>
        <md-button class="" @click="cancel">Deal abbrechen</md-button>
        <md-button class="md-primary" @click="confirm">Deal abschließen</md-button>
    </md-dialog-actions>
</md-dialog>

</template>

<script>

import {
    mapGetters
}
from 'vuex'


export default {
    name: 'ConstructionDialog',
    props: {
        show: Boolean,
        groups: Array,
        gameboard: Array, //fetch this from vuex would be nicer....
        onYes: Function,
        onNo: Function
    },
    computed: {},
    data: function() {
        return {
            show2: false,
            construction: {},
            streets: [{
                name: "Grunewald",
                level: 3,
                showPlus: true,
                showMinus: false
            }, {
                name: "Mitte",
                level: 0,
                showPlus: true,
                showMinus: false
            }],
            costs: 0

        }
    },
    created() {
        for (var i = 0; i < this.streets.length; i++) {
            this.construct(this.streets[i].name, this.streets[i].level);
        }
    },
    watch: {},
    methods: {
        open: function() {
            this.show2 = true;
        },
        hide: function() {
            this.show2 = false;
        },
        construct: function(street, dif) {
            if (this.construction[street]) {
                this.construction[street] += dif;
            } else {
                this.construction[street] = dif;
            }
            this.validate(street);
            this.$forceUpdate();
        },
        validate: function(street) {
            for (var i = 0; i < this.streets.length; i++) {
                if (this.streets[i].name == street) {
                    if (this.construction[this.streets[i].name] == 0) {
                        this.streets[i].showMinus = false;
                        this.streets[i].showPlus = true;
                    }
                    if (this.construction[this.streets[i].name] == 5) {
                        this.streets[i].showMinus = true;
                        this.streets[i].showPlus = false;
                    } else {
                        this.streets[i].showMinus = true;
                        this.streets[i].showPlus = true;
                    }
                }
            }
        },
        cancel: function() {
            this.show2 = false;
            this.onNo();
        },
        confirm: function() {
            this.show2 = false;
            this.onYes({
                //        dices: [this.diceWish1, this.diceWish2]
            });
        }
    }
}

</script>
