<template>
<easel-container ref="box" flip="" :x="x" :y="y" :align="['bottom', 'left']" :rotation="rotation">
  <easel-shape :x="0" :y="0" form="rect" :align="['bottom', 'left']" fill="white" stroke="black" :dimensions="[fieldWidth, fieldLength]">
  </easel-shape>
  <easel-shape v-if="attributes.type == 'street'" :x="0" :y="0" form="rect" :align="['bottom', 'left']" :fill="attributes.color" stroke="black" :dimensions="[20, fieldLength]">
  </easel-shape>
  <easel-bitmap v-if="attributes.type == 'street' && attributes.houses < 5"
    v-for="i in attributes.houses"
    image="/img/icons/house2.png"
    scale="0.025"
    :rotation="-90"
    :x="2"
    :y="fieldLength-2-(15*(i-1))"
    :align="['left','top']"
>
</easel-bitmap>
<easel-bitmap v-if="attributes.type == 'street' && attributes.houses == 5"
  v-for="i in attributes.houses"
  image="/img/icons/hotel1.png"
  scale="0.025"
  :rotation="-90"
  :x="2"
  :y="fieldLength/2+3"
  :align="['left','top']"
>
</easel-bitmap>
  <easel-text
       :rotation="-90"
       :text="name"
       font="11px 'Montserrat'"
       align="['top', 'left']"
       :y="fieldLength-5"
       :x="40"
   >
   </easel-text>
   <easel-text v-if="attributes.price"
        :rotation="-90"
        :text="attributes.price + ' €'"
        font="9px 'Montserrat'"
        color="grey"
        align="['top', 'center']"
        :y="fieldLength-10"
        :x="90"
    >
    </easel-text>
</easel-container>
</template>

<script>

export default {
  name: 'MonopolyField',
  props: {
    label: String,
    x: Number,
    y: Number,
    fieldWidth : Number,
    fieldLength : Number,
    rotation : { type: Number, required: false, default: 0},
    attributes : { type: Object, required: false, default: {"color": "#1d1d1d"}}
  },
  data: function() {
    return {
    }
  },
  computed : {
    color : () => this.$data.attributes.color || '#1d1d1d',
    name: function() {
      return this.label.replace(' ', '\n').replace(/-/g, '-\n');
    },
    center: function() {
      if (this.rotation == 0) {
        return {x: this.x + this.fieldWidth/2, y: this.y + this.fieldLength/2 };
      }
      else if (this.rotation == 90) {
        return {x: this.x - this.fieldWidth/2, y: this.y + this.fieldLength/2 };
      }
      else if (this.rotation == 270) {
        return {x: this.x - this.fieldWidth/2, y: this.y - this.fieldLength/2 };
      }
      else if (this.rotation == 180) {
        return {x: this.x - this.fieldWidth/2, y: this.y - this.fieldLength/2 };
      }
    }
    //label2: () => this.label.replace(' ', '\n')
  }
}
</script>
