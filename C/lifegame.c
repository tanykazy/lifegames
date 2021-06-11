#include "lifegame.h"

int main(int argc, char *argv[])
{
	board *b;
	b = make_board(10, 10);
	print_board(b);
	free(b->s);
	free(b);
	return 0;
}

cells make_cells(int w, int h, board *b)
{
	int i;
	int j;
	cells cells_pp;

	cells_pp = (cells)malloc(sizeof(cell *) * h);
	if (cells_pp == NULL)
	{
		free(b);
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < h; i++)
	{
		cells_pp[i] = (cell *)malloc(sizeof(cell) * w);
		if (cells_pp[i] == NULL)
		{
			for (; i > 0; i--)
			{
				free(cells_pp[i]);
			}
			free(cells_pp);
			free(b);
			exit(EXIT_FAILURE);
		}

		for (j = 0; j < w; j++)
		{
			cells_pp[i][j] = rand_cell();
		}
	}

	return cells_pp;
}

board *make_board(int w, int h)
{
	board *board_p = (board *)malloc(sizeof(board));
	if (board_p == NULL)
	{
		exit(EXIT_FAILURE);
	}

	board_p->w = w;
	board_p->h = h;
	board_p->s = make_cells(w, h, board_p);

	return board_p;
}

cell rand_cell(void)
{
	int c = rand() % 2;
	return (cell)c;
}

void print_board(board *b)
{
	for (int w = 0; w < b->w; w++)
	{
		for (int h = 0; h < b->h; h++)
		{
			if (b->s[h][w] == 0)
			{
				printf("%c", ' ');
			}
			else
			{
				printf("%c", '*');
			}
		}
		printf("%c", '\n');
	}
}
