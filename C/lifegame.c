#include "lifegame.h"

int main(int argc, char *argv[])
{
	board *b_p = NULL;
	result r;
	r = make_board(&b_p, 10, 10);
	if (r == FAILURE)
	{
		free(b_p);
		return EXIT_FAILURE;
	}
	print_board(b_p);
	free(b_p->s);
	free(b_p);
	return EXIT_SUCCESS;
}

result make_board(board **b_pp, int w, int h)
{
	board *b = NULL;
	unsigned int seed;
	result r;

	b = (board *)malloc(sizeof(board));
	if (b == NULL)
	{
		return FAILURE;
	}

	seed = time(NULL);
	srand(seed);

	b->w = w;
	b->h = h;
	r = make_cells(&b->s, w, h);
	if (r == FAILURE)
	{
		free(b);
		return FAILURE;
	}

	*b_pp = b;
	return SUCCESS;
}

result make_cells(cells *c_p, int w, int h)
{
	int i;
	int j;
	cells c = NULL;

	c = (cells)malloc(h * sizeof(cell *));
	if (c == NULL)
	{
		return FAILURE;
	}

	for (i = 0; i < h; i++)
	{
		c[i] = (cell *)malloc(w * sizeof(cell));
		if (c[i] == NULL)
		{
			for (; i > 0; i--)
			{
				free(c[i]);
			}
			free(c);
			return FAILURE;
		}

		for (j = 0; j < w; j++)
		{
			c[i][j] = rand_cell();
		}
	}

	*c_p = c;
	return SUCCESS;
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
