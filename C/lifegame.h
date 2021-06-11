#ifndef __LIFEGAME_H__
#define __LIFEGAME_H__

#include <stdio.h>
#include <stdlib.h>

typedef char cell;
typedef cell **cells;

typedef struct
{
    int w;
    int h;
    cells s;
} board;

cells make_cells(int w, int h, board *b);
board *make_board(int w, int h);
cell rand_cell(void);
void print_board(board *b);

#endif /* __LIFEGAME_H__ */
