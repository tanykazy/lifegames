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
			if b.state[y][x] > 0 {
				buf.WriteByte('1')
			} else {
				buf.WriteByte('0')
			}
		}
		buf.WriteByte('\n')
	}
	return buf.String()
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
	var board = MakeBoard(3, 2)
	fmt.Println(board)
}

