#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "knot.h"

static void do_tile(row_t *rows, int row, int col)
{
	tile_t *t = &rows[row  ].cols[col  ];
	tile_t *l = &rows[row  ].cols[col-1];
	tile_t *u = &rows[row-1].cols[col  ];

	/* Fill in what we know */
	switch (t->c) {
	case '-':  t->top = LEFT | RIGHT; break;
	case '|':  t->top = UP | DOWN;    break;
	case '\'': t->top = UP;           break;
	case '.':  t->top = DOWN;         break;
	}

	/* Follow bottoms */
	if (t->c == '|' && (l->top | l->bot) & RIGHT)
		t->bot = LEFT | RIGHT;
	if (rows[row-1].ncols >= col)
		if (t->c == '-' && (u->top | u->bot) & DOWN)
			t->bot = UP | DOWN;

	/* Adds sides for ''s and .'s */
	if (t->c == '.' || t->c == '\'') {
		if ((l->top | l->bot) & RIGHT)
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
	int row = 1, col = 1;
	row_t *rows = calloc(sizeof(row_t), (row+2));
	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			row++;
			col = 1;
			rows = realloc(rows, sizeof(row_t) * (row+2));
			rows[row+1] = (row_t){};
		} else {
			rows[row].cols = realloc(rows[row].cols, sizeof(tile_t) * (col+1));
			rows[row].ncols = col+1;
			rows[row].cols[col] = (tile_t){};
			rows[row].cols[col].c = c;
			do_tile(rows, row, col);
			col++;
		}
	}

	/* Output */
	//for (row = 1; row < 63; row++) {
	//	for (col = 1; col < 511; col++) {
	//		print_ptrn(tiles[row][col].top);
	//		print_ptrn(tiles[row][col].bot);
	//		printf(" ");
	//	}
	//	printf("\n");
	//}

	/* HTML */
	print_index(rows);
}
