package main

import (
	"fmt"
	"bytes"
	"time"
	"math/rand"
)

type Cell byte
type Cells [][]Cell
type Board struct {
	w, h int
	s Cells
}

func (b *Board) String() string {
	var buf bytes.Buffer
	for y := 0; y < b.h; y++ {
		for x := 0; x < b.w; x++ {
			buf.WriteString(fmt.Sprint(b.s[y][x]))
		}
		buf.WriteByte('\n')
	}
	return buf.String()
}

func (b *Board) Step() {
	n := MakeCells(b.w, b.h)
	for y := 0; y < b.h; y++ {
		for x := 0; x < b.w; x++ {
			c := b.CountNeighbor(x, y)
			if b.s[y][x] > 0 {
				if c == 2 || c == 3 {
					n[y][x] = 1
				} else {
					n[y][x] = 0
				}
			} else {
				if c == 3 {
					n[y][x] = 1
				} else {
					n[y][x] = 0
				}
			}
		}
	}
	b.s = n
}

func (b *Board) CountNeighbor(x, y int) int {
	a := []int{-1, 0, 1}
	n := 0
	for _, i := range a {
		for _, j := range a {
			if i != 0 || j != 0 {
				c := b.ToroidalizeCell(x + j, y + i)
				if c > 0 {
					n++
				}
			}
		}
	}
	return n
}

func (b *Board) ToroidalizeCell(x, y int) Cell {
	y += b.h
	y %= b.h
	x += b.w
	x %= b.w
	return b.s[y][x]
}

func (b *Board) RandomizeCell() {
	for i := 0; i < (b.w * b.h / 2); i++ {
		b.s[rand.Intn(b.h)][rand.Intn(b.w)] = 1
	}
}

func MakeCells(w, h int) Cells {
	c := make(Cells, h)
	for i := range c {
		c[i] = make([]Cell, w)
	}
	return c
}

func MakeBoard(w, h int) *Board {
	return &Board{
		w: w,
		h: h,
		s: MakeCells(w, h),
	}
}

func main() {
	var board = MakeBoard(50, 50)

	board.RandomizeCell()

//	board.s[0][0] = 1
//	board.s[1][0] = 1
//	board.s[2][0] = 1
//	board.s[0][1] = 1
//	board.s[2][2] = 1

	for i := 0; i < 100; i++ {
		fmt.Println(board)
		board.Step()
		time.Sleep(time.Second / 30)
	}
}

