#include <stdio.h>

#include "board.h"

struct game {
	int board[2][7];
	int nrock;
	int *iter;
	int *user;
};
typedef struct game game_t;

static void initgame(game_t *);

int
main()
{
	WINDOW *board;
	game_t game;

	initscr();
	noecho();
	curs_set(0);

	refresh();
        board = newwin(7, 25, 5, 5);
	initboard(board);
	wrefresh(board);

	initgame(&game);

	getch();
	endwin();
}

static void
initgame(game_t *game)
{
	int i;
	for (i = 0; i < 6; i++) {
		game->board[0][i] = 4;
		game->board[1][i] = 4;
	}
	game->user = game->board[0];
}
