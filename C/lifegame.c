#include "lifegame.h"

int main(int argc, char *argv[])
{
	struct board *b_p = NULL;
	result r;

	r = make_board(&b_p, 8, 7);
	if (r == FAILURE)
	{
		return EXIT_FAILURE;
	}

	print_board(b_p);

	free_state(b_p->s);
	free(b_p);
	return EXIT_SUCCESS;
}

result make_board(struct board **b_pp, int w, int h)
{
	struct board *b = NULL;
	unsigned int seed;
	result r;

	b = (struct board *)malloc(sizeof(struct board));
	if (b == NULL)
	{
		return FAILURE;
	}

	seed = time(NULL);
	srand(seed);

	b->w = w;
	b->h = h;
	r = make_state(&b->s);
	if (r == FAILURE)
	{
		free(b);
		return FAILURE;
	}

	r = make_cells(b->s, w, h);
	if (r == FAILURE)
	{
		free(b->s);
		free(b);
		return FAILURE;
	}

	*b_pp = b;
	return SUCCESS;
}

result make_state(struct state **s_pp)
{
	struct state *s = NULL;
	s = (struct state *)malloc(sizeof(struct state));
	if (s == NULL)
	{
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
			c[i][j] = rand_cell();
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

void free_state(struct state *s_p)
{
	free(s_p->_c);
	s_p->_c = NULL;
	free(s_p->c);
	s_p->c = NULL;
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
