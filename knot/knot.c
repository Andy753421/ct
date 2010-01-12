#include <stdio.h>
#include <stdlib.h>

#include "knot.h"

static void do_tile(tile_t **tiles, int row, int col)
{
	tile_t *t = &tiles[row][col];
	tile_t *l = &tiles[row][col-1];
	tile_t *r = &tiles[row][col+1];
	tile_t *u = &tiles[row-1][col];
	//tile_t *d = &tiles[row+1][col];

	/* Fill in what we know */
	switch (tiles[row][col].c) {
	case '-':  t->top = LEFT | RIGHT; break;
	case '|':  t->top = UP | DOWN;    break;
	case '\'': t->top = UP;           break;
	case '.':  t->top = DOWN;         break;
	}

	/* Follow bottoms */
	if (t->c == '|' && (l->top | l->bot) & RIGHT)
		t->bot = LEFT | RIGHT;
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
	tile_t *tiles[64];
	for (int i = 0; i < 64; i++)
		tiles[i] = calloc(512, sizeof(tile_t));

	/* Read data */
	char c;
	int row = 1, col = 1;
	while ((c = getchar()) != EOF) {
		if (row > 63 || col > 511)
			exit(-1);
		if (c == '\n') {
			row++;
			col = 1;
		} else {
			tiles[row][col].c = c;
			col++;
		}
	}

	/* Process */
	for (row = 1; row < 63; row++)
		for (col = 1; col < 511; col++)
			do_tile(tiles, row, col);

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
	print_index(tiles);
}
