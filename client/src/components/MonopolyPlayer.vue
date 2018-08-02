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
    move(fieldIndex) {
      var fieldsPerLine = 10;
      var linesPerGame = 4;

      var line = Math.floor(fieldIndex / fieldsPerLine) % linesPerGame;
      var fieldInLine = fieldIndex % fieldsPerLine;
      var fieldOffset = this.fieldLength / 2;
      var gameOffset = 10;

      if (line == 0) {
        this.x = fieldOffset;
        this.y = 600 - (gameOffset + fieldOffset + fieldInLine * this.fieldLength);
      }
      else if (line == 1) {
        this.x = fieldOffset + fieldInLine * this.fieldLength;
        this.y = fieldOffset;
      }
      else if (line == 2) {
        this.x = 600 - (gameOffset + fieldOffset);
        this.y = fieldOffset + fieldInLine * this.fieldLength;
      }
      else if (line == 3) {
        this.x = 600 - (gameOffset + fieldOffset + fieldInLine * this.fieldLength);
        this.y = 600 - (gameOffset + fieldOffset);
      } 
    }
  }
}
</script>
