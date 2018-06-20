<template>
<easel-container flip="" :x="x" :y="y" :align="['bottom', 'left']">
  <easel-shape :x="0" :y="0" form="rect" :align="['bottom', 'left']" :fill="attributes.color" stroke="black" :dimensions="[fieldWidth, fieldLength]">
  </easel-shape>
  <easel-text
       :text="label"
       font="15px 'Times New Roman'"
       align="['center', 'left']"
       :y="fieldLength/2"
       :x="10"
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
    attributes : { type: Object, required: false, default: {"color": "#1d1d1d"}}
  },
  data: function() {
    return {
    }
  },
  computed : {
    color : () => this.$data.attributes.color || '#1d1d1d'
  }
}
</script>
