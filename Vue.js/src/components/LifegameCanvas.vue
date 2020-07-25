<template>
  <canvas v-bind:width="width" v-bind:height="height" id="lifegame-canvas"></canvas>
</template>

<script>
function getCanvasContext() {
  let canvas = document.getElementById("lifegame-canvas");
  let context = canvas.getContext("2d");
  return context;
}
function life2color(life) {
  if (life === 0) {
    return "rgb(255,255,255)";
  } else if (life === 1) {
    return "rgb(0,0,0)";
  }
}
export default {
  name: "LifegameCanvas",
  data: function () {
    return {
      context: null,
      width: 300,
      height: 300,
      cellsize: 12,
    };
  },
  methods: {
    init: function () {
      this.context = getCanvasContext();
      this.context.fillStyle = "rgb(200, 200, 200)";
      this.context.fillRect(0, 0, this.width, this.height);
    },
    resize: function (width, height, cellsize) {
      this.width = this.context.canvas.width = width * cellsize;
      this.height = this.context.canvas.height = height * cellsize;
      this.cellsize = cellsize;
    },
    fillcell: function (x, y, life) {
      this.context.fillStyle = life2color(life);
      this.context.fillRect(
        x * this.cellsize,
        y * this.cellsize,
        this.cellsize - 1,
        this.cellsize - 1
      );
    },
    // drawcells: function(map){

    // }
  },
  mounted: function () {
    this.context = getCanvasContext();
    // this.resize(20, 20, 12);
    this.init();
    // this.context = getCanvasContext();
    // const context = getCanvasContext();
    // context.fillStyle = "rgb(120,120,120)";
    // context.fillRect(0, 0, this.width, this.height);
    // this.resize(20, 20, 12);
    this.fillcell(5, 5, 1);
    this.fillcell(0, 0, 0);
  },
};
</script>

<style scoped>
#lifegame-canvas {
  border: 1px solid #000000;
}
</style>
