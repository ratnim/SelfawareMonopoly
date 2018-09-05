<template>
<easel-container flip="" :x="x" :y="y" :align="['bottom', 'left']" :rotation="rotation">
  <easel-shape :x="0" :y="0" form="rect" :align="['bottom', 'left']" :fill="attributes.color" stroke="black" :dimensions="[fieldWidth, fieldLength]">
  </easel-shape>
  <easel-text
       :text="label.replace(' ', '\n')"
       font="14px 'Helvetica'"
       align="['center', 'left']"
       :y="fieldLength/2"
       :x="5"
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
    //label2: () => this.label.replace(' ', '\n')
  }
}
</script>
