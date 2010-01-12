enum {
	LEFT  = 1<<0,
	RIGHT = 1<<1,
	UP    = 1<<2,
	DOWN  = 1<<3,
};

typedef struct {
	char c;
	int top;
	int bot;
} tile_t;

typedef struct {
	tile_t *cols;
	int ncols;
} row_t;

void print_index(row_t *rows);
