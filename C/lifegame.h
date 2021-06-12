#ifndef __LIFEGAME_H__
#define __LIFEGAME_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define FAILURE false
#define SUCCESS true

typedef bool result;

typedef char cell;
typedef cell **cells;

typedef struct
{
    int w;
    int h;
    cells s;
} board;

result make_board(board **b_pp, int w, int h);
result make_cells(cells *c_p, int w, int h);
cell rand_cell(void);
void print_board(board *b);

#endif /* __LIFEGAME_H__ */
