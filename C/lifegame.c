#include "lifegame.h"

int main(int argc, char *argv[])
{
	unsigned int seed;
	result r;
	struct board *b_p = NULL;

	seed = time(NULL);
	srand(seed);

	r = make_board(&b_p, 20, 20);
	if (r == FAILURE)
	{
		return EXIT_FAILURE;
	}

	// b_p->s->c[0][0] = 1;
	// b_p->s->c[0][1] = 1;
	// b_p->s->c[0][2] = 1;
	// b_p->s->c[1][0] = 1;
	// b_p->s->c[2][1] = 1;

	for (int i = 0; i < 100; i++)
	{
		print_board(b_p);
		next(b_p);
		// printf("%c", '\n');
	}

	free_state(b_p);
	free(b_p);
	return EXIT_SUCCESS;
}

result next(struct board *b_p)
{
	int i;
	int j;
	int c;
	result r;
	cells next;
	cells current = b_p->s->c;
	int w = b_p->w;
	int h = b_p->h;
	struct state *s = NULL;

	r = make_state(&s, w, h);
	if (r == FAILURE)
	{
		return FAILURE;
	}

	next = s->c;

	for (i = 0; i < w; i++)
	{
		for (j = 0; j < h; j++)
		{
			c = count_neighbor(i, j, b_p);
			if (current[i][j] > 0)
			{
				if (c == 2 || c == 3)
				{
					next[i][j] = 1;
				}
				else
				{
					next[i][j] = 0;
				}
			}
			else
			{
				if (c == 3)
				{
					next[i][j] = 1;
				}
				else
				{
					next[i][j] = 0;
				}
			}
		}
	}

	free_state(b_p);
	b_p->s = s;
	return SUCCESS;
}

int count_neighbor(int x, int y, struct board *b)
{
	int i;
	int j;
	int n = 0;

	for (i = -1; i < 2; i++)
	{
		for (j = -1; j < 2; j++)
		{
			if (i != 0 || j != 0)
			{
				if (toroidalize_cell(x + i, y + j, b) > 0)
				{
					n++;
				}
			}
		}
	}

	return n;
}

cell toroidalize_cell(int x, int y, struct board *b)
{
	x += b->w;
	y += b->h;
	x %= b->w;
	y %= b->h;
	return b->s->c[x][y];
}

result make_board(struct board **b_pp, int w, int h)
{
	struct board *b = NULL;
	result r;

	b = (struct board *)malloc(sizeof(struct board));
	if (b == NULL)
	{
		return FAILURE;
	}

	b->w = w;
	b->h = h;

	r = make_state(&b->s, w, h);
	if (r == FAILURE)
	{
		free(b);
		return FAILURE;
	}

	*b_pp = b;
	return SUCCESS;
}

result make_state(struct state **s_pp, int w, int h)
{
	result r;
	struct state *s = NULL;

	s = (struct state *)malloc(sizeof(struct state));
	if (s == NULL)
	{
		return FAILURE;
	}

	r = make_cells(s, w, h);
	if (r == FAILURE)
	{
		free(s);
		return FAILURE;
	}

	*s_pp = s;
	return SUCCESS;
}

result make_cells(struct state *s_p, int w, int h)
{
	int i;
	int j;
	cells c = NULL;
	cell *_c = NULL;

	c = (cells)malloc(w * sizeof(cell *));
	if (c == NULL)
	{
		return FAILURE;
	}

	_c = (cell *)malloc(w * h * sizeof(cell));
	if (_c == NULL)
	{
		free(c);
		return FAILURE;
	}

	for (i = 0; i < w; i++)
	{
		c[i] = _c + i * h;
	}

	for (i = 0; i < w; i++)
	{
		for (j = 0; j < h; j++)
		{
			// c[i][j] = rand_cell();
			c[i][j] = 0;
		}
	}

	s_p->c = c;
	s_p->_c = _c;
	return SUCCESS;
}

cell rand_cell(void)
{
	int c = rand() % 2;
	return (cell)c;
}

void free_state(struct board *b_p)
{
	free(b_p->s->_c);
	b_p->s->_c = NULL;
	free(b_p->s->c);
	b_p->s->c = NULL;
	free(b_p->s);
	b_p->s = NULL;
}

void print_board(struct board *b)
{
	int i;
	int j;
	int h = b->h;
	int w = b->w;
	cells c = b->s->c;

	for (i = 0; i < w; i++)
	{
		for (j = 0; j < h; j++)
		{
			if (c[i][j] == 0)
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
