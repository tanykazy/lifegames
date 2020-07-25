<template>
  <svg
    id="grid"
    v-bind:width="width"
    v-bind:height="height"
    v-bind:viewBox="viewBox"
    v-on:click.left="click"
  />
</template>

<script>
const namespace4svg = "http://www.w3.org/2000/svg";

function getSvg() {
  let svg = document.getElementById("grid");
  return svg;
}

function clearSvg() {
  let svg = getSvg();
  while (svg.firstChild) {
    svg.removeChild(svg.firstChild);
  }
}

function createSVGRectElement(x, y, width, height, rx, ry) {
  let rect = document.createElementNS(namespace4svg, "rect");
  x && rect.setAttribute("x", x);
  y && rect.setAttribute("y", y);
  width && rect.setAttribute("width", width);
  height && rect.setAttribute("height", height);
  rx && rect.setAttribute("rx", rx);
  ry && rect.setAttribute("ry", ry);
  return rect;
}

function appendRect(x, y, width, height, color) {
  let rect = createSVGRectElement(x, y, width, height);
  rect.style.fill = color;
  let svg = getSvg();
  svg.appendChild(rect);
}

function removeRect(x, y) {
  let svg = getSvg();
  if (svg.hasChildNodes()) {
    let childNodes = svg.childNodes;
    for (let index = 0; index < childNodes.length; index++) {
      let child = childNodes[index];
      if (child.x === x && child.y === y) {
        svg.removeChild(child);
      }
    }
  }
}

export default {
  name: "LifegameGrid",
  data: function () {
    return {
      width: 0,
      height: 0,
      viewBox: "0 0 0 0",
    };
  },
  props: {
    row: Number,
    column: Number,
    cellsize: Number,
    map: Array,
  },
  watch: {
    map: {
      handler: function (map) {
        this.drawcells(map);
      },
    },
  },
  methods: {
    drawcell: function (x, y) {
      x = x * this.cellsize;
      y = y * this.cellsize;
      appendRect(x, y, this.cellsize, this.cellsize, "rgb(0,0,0)");
    },
    drawcells: function (map) {
      this.cleargrid();
      for (let x = 0; x < map.length; x++) {
        for (let y = 0; y < map[x].length; y++) {
          if (map[x][y] > 0) {
            this.drawcell(x, y);
          }
        }
      }
    },
    clearcell: function (x, y) {
      x = x * this.cellsize;
      y = y * this.cellsize;
      removeRect(x, y);
    },
    cleargrid: function () {
      clearSvg();
    },
    click: function (event) {
      if (
        0 < event.offsetX &&
        event.offsetX < this.width &&
        0 < event.offsetY &&
        event.offsetY < this.height
      ) {
        let x = Math.floor(event.offsetX / this.cellsize);
        let y = Math.floor(event.offsetY / this.cellsize);
        this.$emit("click-grid", { x: x, y: y, event });
      }
    },
  },
  mounted: function () {
    this.width = this.row * this.cellsize;
    this.height = this.column * this.cellsize;
    this.viewBox = [0, 0, this.width, this.height].join(" ");
  },
};
</script>

<style scoped>
#grid {
  border: 1px solid #000000;
}
</style>