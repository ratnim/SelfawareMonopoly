<template>
  <easel-shape :x="x" :y="y" form="circle" :fill="color" stroke="black" :dimensions="diameter" name="player1">
  </easel-shape>
</template>

<script>
export default {
  name: 'MonopolyPlayer',
  props: {
    lane : {type: Number, default: 1},
    diameter : {type: Number, default: 10},
    fieldLength : Number,
    color: {type: String, default: "#FF0000"},
    id: {type: Number, default: 0},
  },
  data: function() {
    return {
      x: 40,
      y: 600-50
    }
  },
  computed : {
    //x : () => 10 + 30,
    //y : () => 600 - 10 - this.fieldLength/2
  },
  mounted() {
    //debugger;
    this.x = 10 + 30;
    this.y = 600 - 10 - this.fieldLength / 2;
  },
  methods : {
    move(x, y) {
      this.x = x;
      this.y = y;
    }
  }
}
</script>
