/**
 * Return state next generation in Conway's life game.
 * Rule is 23/3.
 * @param {string} state JSON string of 2D array
 * @return {string} Next state of input
 */
function lifegame(state) {
    const s = JSON.parse(state);
    const n = [];
    for (let x = 0; x < s.length; x++) {
        n[x] = [];
        for (let y = 0; y < s[x].length; y++) {
            let c = 0;
            const a = [-1, 0, 1];
            for (const i of a) {
                for (const j of a) {
                    if (i != 0 || j != 0) {
                        if (s[(x + i + s.length) % s.length][(y + j + s[x].length) % s[x].length] == 1) {
                            c++;
                        }
                    }
                }
            }
            if (s[x][y] === 1) {
                if (c === 2 || c === 3) {
                    n[x][y] = 1;
                } else {
                    n[x][y] = 0;
                }
            } else {
                if (c === 3) {
                    n[x][y] = 1;
                } else {
                    n[x][y] = 0;
                }
            }
        }
    }
    return JSON.stringify(n);
}
