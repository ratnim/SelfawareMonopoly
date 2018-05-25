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
    color: {type: String, default: "#FF0000"}
  },
  data: function() {
    return {
      x: 40,
      y: 600-30
    }
  },
  computed : {
    //x : () => 10 + 30,
    //y : () => 600 - 10 - this.fieldLength/2
  },
  mounted() {
    //debugger;
    this.x = 10 + 30;
    this.y = 600 - 10 - this.fieldLength/2;
  },
  methods : {
    move(fieldIndex) {
      //which line
      var fieldsperLine = 7;
      if (Math.floor(fieldIndex/fieldsperLine)==0) {
        this.x = 10 + 30;
        this.y = 600-10-(fieldIndex%fieldsperLine)*this.fieldLength-this.fieldLength/2;
      } else {
        this.x = 300;
        this.y = 300;
      }

    }
  }
}
</script>
