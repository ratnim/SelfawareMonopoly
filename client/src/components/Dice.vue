<template>
<span>
<span v-for="(row, rowi) in diceCoords">
<easel-shape v-for="(coords, index) in row" v-if="_show(rowi, index)" :x="coords[0]" :y="coords[1]" form="circle" fill="black" stroke="black" :dimensions="diameter">
</easel-shape>
</span>
</span>
</template>

<script>
export default {
  name: 'Dice',
  props: {
    x: {
      type: Number,
      default: 300
    },
    y: {
      type: Number,
      default: 300
    }
  },
  data: function() {
    return {
      diameter: 5,
      gap: 8,
      dice: null,
      //x: 300,
      //y: 300,
      diceCoords: [],
      diceTemplate: {
        1: ['ooo', 'oxo', 'ooo'],
        2: ['xoo', 'ooo', 'oox'],
        3: ['xoo', 'oxo', 'oox'],
        4: ['xox', 'oxo', 'xox'],
        5: ['xox', 'oxo', 'xox'],
        6: ['xox', 'xox', 'xox']
      }
    }
  },
  computed: {},
  mounted() {
    this.diceCoords = [
      [
        [this.x - this.gap - this.diameter, this.y - this.gap - this.diameter],
        [this.x, this.y - this.gap - this.diameter],
        [this.x + this.gap + this.diameter, this.y - this.gap - this.diameter]
      ],
      [
        [this.x - this.gap - this.diameter, this.y],
        [this.x, this.y],
        [this.x + this.gap + this.diameter, this.y]
      ],
      [
        [this.x - this.gap - this.diameter, this.y + this.gap + this.diameter],
        [this.x, this.y + this.gap + this.diameter],
        [this.x + this.gap + this.diameter, this.y + this.gap + this.diameter]
      ]
    ]
  },
  methods: {
    _show(row, index) {
      if (this.dice > 6 || this.dice < 1) {
        return false; //hide
      }
      return this.diceTemplate[this.dice][row][index] == 'x'
    },
    animate() {
      this.interval = setInterval(() => {
        this.dice = parseInt(Math.random() * 6) + 1
      }, 180);


    },
    show(eyes) {
      //int values from 1 to 6
      if (this.interval) {
        clearInterval(this.interval);
      }
      this.dice = eyes;
    }
  }
}
</script>
