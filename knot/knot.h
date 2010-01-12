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

void print_index(tile_t **tiles);
