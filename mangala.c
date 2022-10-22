#include <stdio.h>

#include "board.h"

enum {
	USER_AREA,
	ENEMY_AREA,
};
struct game {
	int board[2][7];
	int nrock;
	int *iter;
	int *user;
};
typedef struct game game_t;

static int getuser(game_t *);
static int location(game_t *);
static int *getenemyarea(game_t *);
static void change_user(game_t *);
static void endturn(game_t *);
static void initgame(game_t *);
static void initturn(game_t *, int);
static void iterate(game_t *);
static void playturn(game_t *);

static int
getuser(game_t *game)
{
	return game->user == game->board[0] ? 0 : 1;
}

static int *
getenemyarea(game_t *game)
{
	return game->iter;
}

static int
location(game_t *game)
{
	if (game->user < game->board[1])
		return USER_AREA;
	else
		return ENEMY_AREA;
}

static void
change_user(game_t *game)
{
	if (game->user == game->board[0])
		game->user = game->board[1];
	else
		game->user = game->board[0];
}

static void
endturn(game_t *game)
{
	int *enemyarea;
	int loc = location(game);

	if (loc == USER_AREA && *game->iter == 1) {
		enemyarea = getenemyarea(game);
		game->user[6] += *enemyarea;
		*enemyarea = 0;
		game->user[6]++;
		*game->iter = 0;
	} else if (loc == ENEMY_AREA && *game->iter % 2 == 0) {
		game->user[6] += *game->iter;
		*game->iter = 0;
	}

	change_user(game);
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

	if (game->nrock > 1) {
		game->nrock--;
		(*game->iter)++;
	}
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
		iterate(game);
		(*game->iter)++;
		game->nrock--;
	}
}

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
		switch (ch) {
		case 't':
			change_user(&game);
			break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
			ch -= 48;

			/* here are some turn initing or playing actions */
			initturn(&game, ch-1);
			playturn(&game);
			endturn(&game);

#ifdef DEBUG
			mvwprintw(bottom, 1, 0, "selection: %d", ch);
			wclrtoeol(bottom);
			mvwprintw(bottom, 2, 0, "nrock: %d", game.nrock);
			wclrtoeol(bottom);
#endif
			break;
		default:
			mvwaddstr(bottom, 1, 0, "invalid selection. try again");
			break;
		}

		mvwprintw(bottom, 3, 0, "turn at user %d", getuser(&game));
		/* and then redrawing of board window */
		fillboard(board, game.board);
		wrefresh(board);
		wrefresh(bottom);
	}

	endwin();
}
