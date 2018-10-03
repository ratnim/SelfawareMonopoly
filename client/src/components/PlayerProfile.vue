<template>
  <md-card>
<md-card-header>
  <md-card-header-text>
    <div class="md-title" v-bind:style="{ color: player.color}">{{player.nickname}}
      <img v-show="player.isOnTurn" style="height:30px" src="/img/icons/dices.png" alt="(ist am Zug)">
    </div>
    <div class="md-subhead">{{player.deposit}} €</div>
  </md-card-header-text>

  <!--<md-card-media md-small>
    <img src="/assets/examples/cover.png" alt="People">
  </md-card-media>-->
</md-card-header>


<md-card-content>
  <div v-for="prop in orderedProperties" :key="prop.name" v-bind:style="{ background: prop.attributes.color}">
    {{prop.name.replace(/-/g, '')}}
  </div>

     </md-card-content>

<!--
<md-card-actions>
  <md-button md-small>Handel vorschlagen</md-button>
</md-card-actions> -->
</md-card>
</template>

<script>
import _ from 'lodash'


export default {
  name: 'PlayerProfile',
  props: {
    name: String,
    player: Object
  },
  data: function() {
    return {
    }
  },
  computed : {
    color : () =>  '#1d1d1d',
    orderedProperties: function () {
    return _.orderBy(this.player.properties, 'attributes.index')
  }

    //label2: () => this.label.replace(' ', '\n')
  }
}
</script>
