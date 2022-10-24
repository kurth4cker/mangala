/* mangala.c --- game related functions and main()
 *
 * Copyright 2022 kurth4cker
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the license at
 *
 * 	http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#include <ncurses.h>
#include <mangala.h>

#include "board.h"

typedef struct mgl_game game_t;

static int getuser(game_t *);
static void change_user(game_t *);
static void initturn(game_t *, int);
static void iterate(game_t *);
static void playturn(game_t *);

static int
getuser(game_t *game)
{
	return game->user == game->board[0] ? 0 : 1;
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
	mgl_initgame(&game);
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
