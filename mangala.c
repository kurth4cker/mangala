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
	WINDOW *bottom;
	game_t game;
	int ch;
	int maxx;

	initscr();
	noecho();
	curs_set(0);

	maxx = getmaxx(stdscr);

	refresh();
	board = newwin(7, 25, 5, 5);
	bottom = newwin(4, maxx, 13, 3);

	initboard(board);
	initgame(&game);
	fillboard(board, game.board);
	wrefresh(board);

	mvwaddstr(bottom, 0, 0, "press a number between 1 and 6 to select a XXX");
	wrefresh(bottom);
	while ((ch = getch()) != 'q') {
		ch -= 48;
		if (ch < 1 || ch > 6) {
			mvwaddstr(bottom, 1, 0, "invalid selection. try again");
			wrefresh(bottom);
			continue;
		}

		/* here are some turn initing or playing actions */
		/* and then redrawing of board window */
		fillboard(board, game.board);
		wrefresh(board);
	}

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
