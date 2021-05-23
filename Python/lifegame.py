#! /usr/bin/env python

from random import choice

class Board:
    def __init__(self, h, w):
        self.h = h
        self.w = w
        self.s = self.makecells(h, w)
        self.randomize()
#        self.s[0][0] = 1
#        self.s[1][0] = 1
#        self.s[2][0] = 1
#        self.s[0][1] = 1
#        self.s[2][2] = 1

    def __str__(self):
        a = []
        for c in self.s:
            b = ''
            for l in c:
                b += str(l)
            a.append(b)
        return '\n'.join(a)

    def makecells(self, h, w):
        return [[0 for x in range(w)]for y in range(h)]

    def toroidalize(self, y, x):
        y += self.h
        y %= self.h
        x += self.w
        x %= self.w
        return (y, x)

    def countneighbor(self, y, x):
        n = 0
        a = [-1, 0, 1]
        for i in a:
            for j in a:
                if i != 0 or j != 0:
                    ty, tx = self.toroidalize(y + i, x + j)
                    if self.s[ty][tx] > 0:
                        n += 1
        return n

    def step(self):
        n = self.makecells(self.h, self.w)
        for y in range(self.h):
            for x in range(self.w):
                c = self.countneighbor(y, x)
                if self.s[y][x] > 0:
                    if c == 2 or c == 3:
                        n[y][x] = 1
                    else:
                        n[y][x] = 0
                else:
                    if c == 3:
                        n[y][x] = 1
                    else:
                        n[y][x] = 0
        self.s = n

    def randomize(self):
        for y in range(self.h):
            for x in range(self.w):
                self.s[y][x] = choice([0, 1])


if __name__ == "__main__":
    from shutil import get_terminal_size
    from time import sleep

    ts = get_terminal_size()
    board = Board(ts.lines - 1, ts.columns)
    for i in range(300):
        print(board)
        board.step()
        sleep(1 / 10)
