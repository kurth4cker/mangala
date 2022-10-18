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
static void initturn(game_t *, int);
static void iterate(game_t *);
static void playturn(game_t *);

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
		initturn(&game, ch-1);
		playturn(&game);

#ifdef DEBUG
		mvwprintw(bottom, 1, 0, "selection: %d", ch);
		mvwprintw(bottom, 2, 0, "nrock: %d", game.nrock);
		wrefresh(bottom);
#endif

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

static void
initturn(game_t *game, int sel)
{
	game->iter = &game->user[sel];
	game->nrock = *game->iter;
	*game->iter = 0;
}

static void
iterate(game_t *game)
{
	if (game->iter == &game->board[0][6])
		game->iter = game->board[1];
	else if (game->iter == &game->board[1][6])
		game->iter = game->board[0];
	else
		game->iter++;
}

static void
playturn(game_t *game)
{
	while (game->nrock > 0) {
		(*game->iter)++;
		game->nrock--;
		iterate(game);
	}
}
