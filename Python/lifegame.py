#! /usr/bin/env python

from random import choice

class Board:
    def __init__(self, w, h):
        self.__w = w
        self.__h = h
        self.__s = self.__makecells(w, h)
        self.randomize()
#        self.__s[0][0] = 1
#        self.__s[1][0] = 1
#        self.__s[2][0] = 1
#        self.__s[0][1] = 1
#        self.__s[2][2] = 1

    def __str__(self):
        a = []
        for c in self.__s:
            b = ''
            for l in c:
                b += str(l)
            a.append(b)
        return '\n'.join(a)

    def __makecells(self, w, h):
        return [[0 for x in range(w)]for y in range(h)]

    def __getcell(self, y, x):
        return self.__s[y][x]

    def __toroidalize(self, y, x):
        y += self.__h
        y %= self.__h
        x += self.__w
        x %= self.__w
        return (y, x)

    def __countneighbor(self, y, x):
        n = 0
        a = [-1, 0, 1]
        for i in a:
            for j in a:
                if i != 0 or j != 0:
                    c = self.__getcell(*self.__toroidalize(y + i, x + j))
                    if c > 0:
                        n += 1
        return n

    def step(self):
        n = self.__makecells(self.__w, self.__h)
        for y in range(len(self.__s)):
            for x in range(len(self.__s[y])):
                c = self.__countneighbor(y, x)
                if self.__getcell(y, x) > 0:
                    if c == 2 or c == 3:
                        n[y][x] = 1
                    else:
                        n[y][x] = 0
                else:
                    if c == 3:
                        n[y][x] = 1
                    else:
                        n[y][x] = 0
        self.__s = n

    def randomize(self):
        for y in range(self.__h):
            for x in range(self.__w):
                self.__s[y][x] = choice([0, 1])


if __name__ == "__main__":
    from shutil import get_terminal_size
    from time import sleep

    ts = get_terminal_size()
    board = Board(ts.columns, ts.lines - 1)
    for i in range(300):
        print(board)
        board.step()
        sleep(1 / 10)

