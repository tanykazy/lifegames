#include <stdio.h>
#include <stdlib.h>


typedef char cell;
typedef cell** cells;

typedef struct {
	int w;
	int h;
	cells s;
} board;


cells make_cells(int w, int h, board* b)
{
	int i;
	int j;
	cells cells_pp;

	cells_pp = (cells)malloc(sizeof(cell*) * h);
	if(cells_pp == NULL)
	{
		free(b);
		exit(EXIT_FAILURE);
	}

	for(i = 0; i < h; i++)
	{
		cells_pp[i] = (cell*)malloc(sizeof(cell) * w);
		if(cells_pp[i] == NULL)
		{
			for(; i > 0; i--)
			{
				free(cells_pp[i]);
			}
			free(cells_pp);
			free(b);
			exit(EXIT_FAILURE);
		}

		for(j = 0; j < w; j++)
		{
			cells_pp[i][j] = 0;
		}
	}

	return cells_pp;
}

board *make_board(int w, int h)
{
	board* board_p = (board*)malloc(sizeof(board));
	if(board_p == NULL)
	{
		exit(EXIT_FAILURE);
	}

	board_p->w = w;
	board_p->h = h;
	board_p->s = make_cells(w, h, board_p);

	return board_p;
}

int main(int argc, char* argv[])
{
	board *b;
	b = make_board(10, 10);

	free(b->s);
	free(b);
	return 0;
}

