#include "lifegame.h"

int main(int argc, char *argv[], char **envp)
{
	unsigned int seed;
	result r;
	struct board *b_p = NULL;
	int w;
	int h;
	int s;
	int i;

	seed = time(NULL);
	srand(seed);

	w = read_width(argc, argv);
	h = read_height(argc, argv);
	s = read_step(argc, argv);

	r = make_board(&b_p, w, h);
	if (r == FAILURE)
	{
		return EXIT_FAILURE;
	}

	init_state(b_p);

	for (i = 0; i < s; i++)
	{
		next(b_p);
	}

	print_board(b_p);

	free_state(b_p);
	free(b_p);
	return EXIT_SUCCESS;
}

result next(struct board *b_p)
{
	int x;
	int y;
	int c;
	result r;
	cells n;
	cells current = b_p->s->c;
	int w = b_p->w;
	int h = b_p->h;
	struct state *s = NULL;

	r = make_state(&s, w, h);
	if (r == FAILURE)
	{
		return FAILURE;
	}

	n = s->c;

	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			c = count_neighbor(x, y, b_p);
			if (current[y][x] > 0)
			{
				if (c == 2 || c == 3)
				{
					n[y][x] = 1;
				}
				else
				{
					n[y][x] = 0;
				}
			}
			else
			{
				if (c == 3)
				{
					n[y][x] = 1;
				}
				else
				{
					n[y][x] = 0;
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
	x %= b->w;
	y += b->h;
	y %= b->h;
	return b->s->c[y][x];
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

	c = (cells)malloc(h * sizeof(cell *));
	if (c == NULL)
	{
		return FAILURE;
	}

	_c = (cell *)malloc(h * w * sizeof(cell));
	if (_c == NULL)
	{
		free(c);
		return FAILURE;
	}

	for (i = 0; i < h; i++)
	{
		c[i] = _c + i * w;
	}

	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			c[i][j] = 0;
		}
	}

	s_p->c = c;
	s_p->_c = _c;
	return SUCCESS;
}

void init_state(struct board *b_p)
{
	int ch;
	int x = 0;
	int y = 0;
	int w = b_p->w;
	int h = b_p->h;
	cells c = b_p->s->c;

	if (isatty(fileno(stdin)) == 0)
	{
		while ((ch = getc(stdin)) != EOF)
		{
			if (y < h)
			{
				if (ch == '\n')
				{
					y++;
					x = 0;
				}
				else
				{
					if (x < w)
					{
						if (ch == '0')
						{
							c[y][x] = 0;
						}
						else if (ch == '1')
						{
							c[y][x] = 1;
						}
						x++;
					}
					else
					{
						continue;
					}
				}
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		// c[0][0] = 1;
		// c[0][1] = 1;
		// c[0][2] = 1;
		// c[1][0] = 1;
		// c[2][1] = 1;
		for (y = 0; y < h; y++)
		{
			for (x = 0; x < w; x++)
			{
				c[y][x] = rand_cell();
			}
		}
	}
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

	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			if (c[i][j] == 0)
			{
				putc('0', stdout);
			}
			else
			{
				putc('1', stdout);
			}
		}
		putc('\n', stdout);
	}
}

int read_width(int argc, char *argv[])
{
	int i;
	int w = 0;
	for (i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-w") == 0)
		{
			if (i + 1 < argc)
			{
				w = atoi(argv[i + 1]);
			}
		}
	}
	if (w > 0)
	{
		return w;
	}
	return DEFAULT_WIDTH;
}

int read_height(int argc, char *argv[])
{
	int i;
	int h = 0;
	for (i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-h") == 0)
		{
			if (i + 1 < argc)
			{
				h = atoi(argv[i + 1]);
			}
		}
	}
	if (h > 0)
	{
		return h;
	}
	return DEFAULT_HEIGHT;
}

int read_step(int argc, char *argv[])
{
	int i;
	int s = 0;
	for (i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-s") == 0)
		{
			if (i + 1 < argc)
			{
				s = atoi(argv[i + 1]);
			}
		}
	}
	if (s > 0)
	{
		return s;
	}
	return DEFAULT_STEP;
}
