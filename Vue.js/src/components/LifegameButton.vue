<template>
  <form>
    <input type="button" value="start" id="lifegamestart" v-on:click="clickStart" />
    <input type="button" value="stop" id="lifegamestop" v-on:click="clickStop" />
  </form>
</template>

<script>
export default {
  name: "LifegameButton",
  methods: {
    clickStart: function () {
      this.$emit("start");
    },
    clickStop: function () {
      this.$emit("stop");
    },
  },
  mounted: function () {},
};
</script>

<style scoped>
</style>