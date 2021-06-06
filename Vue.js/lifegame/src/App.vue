<template>
  <div id="lifegame">
    <lifegame-button
      v-on:start="startGame"
      v-on:stop="stopGame"
    ></lifegame-button>
    <lifegame-grid
      v-bind:row="row"
      v-bind:column="column"
      v-bind:cellsize="cellsize"
      v-bind:map="map"
      v-on:click-grid="clickGrid"
    ></lifegame-grid>
  </div>
</template>

<script>
import LifegameGrid from "./components/LifegameGrid.vue";
import LifegameButton from "./components/LifegameButton.vue";

function setInterval(func, delay, ...params) {
  return window.setInterval(func, delay, ...params);
}

function clearInterval(id) {
  window.clearInterval(id);
}

export default {
  name: "Lifegame",
  components: {
    LifegameGrid,
    LifegameButton,
  },
  data: function () {
    return {
      row: 0,
      column: 0,
      cellsize: 12,
      map: null,
      timer: {
        id: 0,
        interval: 200,
      },
    };
  },
  watch: {},
  methods: {
    init: function () {
      this.row = 30;
      this.column = 30;
      this.map = [];
      for (let x = 0; x < this.row; x++) {
        this.map[x] = [];
        for (let y = 0; y < this.column; y++) {
          this.map[x][y] = 0;
        }
      }
    },
    clickGrid: function (position) {
      if (this.map[position.x][position.y] > 0) {
        this.map[position.x][position.y] = 0;
      } else {
        this.map[position.x][position.y] = 1;
      }
      this.map = this.map.slice();
    },
    startGame: function () {
      if (!this.timer.id) {
        this.timer.id = setInterval(this.nextGeneration, this.timer.interval);
      }
    },
    stopGame: function () {
      clearInterval(this.timer.id);
      this.timer.id = 0;
    },
    nextGeneration: function () {
      let next = [];
      for (let x = 0; x < this.row; x++) {
        next[x] = [];
        for (let y = 0; y < this.column; y++) {
          let count = this.countNeighbor(x, y);
          if (this.map[x][y] > 0) {
            if (count == 2 || count == 3) {
              next[x][y] = 1;
            } else {
              next[x][y] = 0;
            }
          } else {
            if (count == 3) {
              next[x][y] = 1;
            } else {
              next[x][y] = 0;
            }
          }
        }
      }
      this.map = next;
    },
    countNeighbor: function (x, y) {
      return (
        this.map[(x + this.row - 1) % this.row][
          (y + this.column - 1) % this.column
        ] +
        this.map[(x + this.row - 1) % this.row][y % this.column] +
        this.map[(x + this.row - 1) % this.row][(y + 1) % this.column] +
        this.map[x % this.row][(y + this.column - 1) % this.column] +
        this.map[x % this.row][(y + 1) % this.column] +
        this.map[(x + 1) % this.row][(y + this.column - 1) % this.column] +
        this.map[(x + 1) % this.row][y % this.column] +
        this.map[(x + 1) % this.row][(y + 1) % this.column]
      );
    },
  },
  created: function () {},
  mounted: function () {
    this.$nextTick(this.init());
  },
};
</script>

<style>
#lifegame {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}
</style>
