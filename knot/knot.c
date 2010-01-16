#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "knot.h"

static void do_tile(row_t *rows, int row, int col)
{
	tile_t *t = &rows[row].cols[col];

	/* Fill in what we know */
	switch (t->c) {
	case '-':  t->top = LEFT | RIGHT; break;
	case '|':  t->top = UP | DOWN;    break;
	case '\'': t->top = UP;           break;
	case '.':  t->top = DOWN;         break;
	}

	/* Follow bottoms */
	if (col > 0) {
		tile_t *l = &rows[row].cols[col-1];
		if (t->c == '|' && (l->top | l->bot) & RIGHT)
			t->bot = LEFT | RIGHT;
	}
	if (row > 0 && rows[row-1].ncols > col) {
		tile_t *u = &rows[row-1].cols[col];
		if (t->c == '-' && (u->top | u->bot) & DOWN)
			t->bot = UP | DOWN;
	}

	/* Adds sides for ''s and .'s */
	if (t->c == '.' || t->c == '\'') {
		tile_t *l = &rows[row].cols[col-1];
		if (col > 0 && (l->top | l->bot) & RIGHT)
			t->top |= LEFT;
		else
			t->top |= RIGHT;
	}

}

static void print_ptrn(int ptrn)
{
	printf("%c", ptrn & LEFT  ? '<' : '-');
	printf("%c", ptrn & RIGHT ? '>' : '-');
	printf("%c", ptrn & UP    ? '^' : '-');
	printf("%c", ptrn & DOWN  ? 'v' : '-');
}

int main()
{
	/* Init tiles */
	char c;
	int row = 0, col = 0;
	row_t *rows = calloc(sizeof(row_t), (row+2));
	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			row++;
			col = 0;
			rows = realloc(rows, sizeof(row_t) * (row+2));
			rows[row+0] = (row_t){.ncols =  0};
			rows[row+1] = (row_t){.ncols = -1};
		} else {
			rows[row].cols = realloc(rows[row].cols, sizeof(tile_t) * (col+1));
			rows[row].ncols = col+1;
			rows[row].cols[col] = (tile_t){.c = c};
			do_tile(rows, row, col);
			col++;
		}
	}

	/* Output */
	if (0)
	for (row = 0; rows[row].ncols >= 0; row++) {
		for (col = 0; col > rows[row].ncols; col++) {
			print_ptrn(rows[row].cols[col].top);
			print_ptrn(rows[row].cols[col].bot);
			printf(" ");
		}
		printf("\n");
	}

	/* HTML */
	print_index(rows);

	/* Free tile */
	for (int row = 0; rows[row].ncols >= 0; row++)
		if (rows[row].cols > 0)
			free(rows[row].cols);
	free(rows);

	return 0;
}
