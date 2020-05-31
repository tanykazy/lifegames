/**
 * Return state next generation in Conway's life game.
 * Rule is 23/3.
 * @param {string} state JSON string of 2D array
 * @return {string} Next state of input
 */
function lifegame(state) {
    let current = JSON.parse(state);
    let next = [];
    for (let x = 0; x < current.length; x++) {
        next[x] = [];
        for (let y = 0; y < current[x].length; y++) {
            let neighbor = current[(x + current.length - 1) % current.length][(y + current[x].length - 1) % current[x].length]
                + current[(x + current.length - 1) % current.length][y]
                + current[(x + current.length - 1) % current.length][(y + 1) % current[x].length]
                + current[x][(y + current[x].length - 1) % current[x].length]
                + current[x][(y + 1) % current[x].length]
                + current[(x + 1) % current.length][(y + current[x].length - 1) % current[x].length]
                + current[(x + 1) % current.length][y]
                + current[(x + 1) % current.length][(y + 1) % current[x].length];
            if (current[x][y] === 1) {
                if (neighbor === 2 || neighbor === 3) {
                    next[x][y] = 1;
                } else {
                    next[x][y] = 0;
                }
            } else {
                if (neighbor === 3) {
                    next[x][y] = 1;
                } else {
                    next[x][y] = 0;
                }
            }
        }
    }
    return JSON.stringify(next);
}

function test() {
    var state = JSON.stringify([
        [1, 1, 1, 0, 0],
        [1, 0, 0, 0, 0],
        [0, 1, 0, 0, 0],
        [0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0]
    ]);
    console.log(state);
    for (var i = 0; i < 10; i++) {
        var result = lifegame(state);
        console.log(result);
        state = result;
    }
}

test();
