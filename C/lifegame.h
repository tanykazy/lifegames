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

struct board
{
    int w;
    int h;
    struct state *s;
};

struct state
{
    cells c;
    cell *_c;
};

result next(struct board *b_p);
int count_neighbor(int x, int y, struct board *b);
cell toroidalize_cell(int x, int y, struct board *b);
result make_board(struct board **b_pp, int w, int h);
result make_state(struct state **s_pp, int w, int h);
result make_cells(struct state *s_p, int w, int h);
cell rand_cell(void);
void free_state(struct board *b_p);
void print_board(struct board *b);

#endif /* __LIFEGAME_H__ */
