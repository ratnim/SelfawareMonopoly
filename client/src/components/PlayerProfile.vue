<template>
  <md-card>
<md-card-header>
  <md-card-header-text>
    <div class="md-title" v-bind:style="{ color: player.color}">{{player.nickname}}</div>
    <div class="md-subhead">{{player.deposit}} €</div>
    <div v-show="player.isOnTurn">
      (ist am Zug)
    </div>
  </md-card-header-text>

  <!--<md-card-media md-small>
    <img src="/assets/examples/cover.png" alt="People">
  </md-card-media>-->
</md-card-header>


<md-card-content>
  <div v-for="prop in player.properties">
    {{prop.name}}
  </div>

     </md-card-content>

<!--
<md-card-actions>
  <md-button md-small>Handel vorschlagen</md-button>
</md-card-actions> -->
</md-card>
</template>

<script>
export default {
  name: 'PlayerProfile',
  props: {
    name: String,
    player: Object
  },
  data: function() {
    return {
      owns: ["a", "b"]
    }
  },
  computed : {
    color : () =>  '#1d1d1d',
    //label2: () => this.label.replace(' ', '\n')
  }
}
</script>
