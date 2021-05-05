package main

import (
	"fmt"
	"bytes"
)

type Cell byte
type Cells [][]Cell
type Board struct {
	w, h int
	state Cells
}

func (b *Board) String() string {
	var buf bytes.Buffer
	for y := 0; y < b.h; y++ {
		for x := 0; x < b.w; x++ {
			buf.WriteString(fmt.Sprint(b.state[y][x]))
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
		}
	}

}

func (b *Board) CountNeighbor(x, y int) int {
	a := []int{-1, 1}
	n := 0
	for _, i := range a {
		for _, j := range a {
			c := b.ToroidalizeCell(x + j, y + i)
		}
	}
	return n
}

func (b *Board) ToroidalizeCell(x, y int) Cell {
	y += b.h
	y %= b.h
	x += b.w
	x %= b.w
	return b.state[y][x]
}

func MakeCells(w, h int) Cells {
	cells := make(Cells, h)
	for i := range cells {
		cells[i] = make([]Cell, w)
	}
	return cells
}

func MakeBoard(w, h int) *Board {
	return &Board{
		w: w,
		h: h,
		state: MakeCells(w, h),
	}
}

func main() {
	var board = MakeBoard(5, 10)
	fmt.Println(board)
}

