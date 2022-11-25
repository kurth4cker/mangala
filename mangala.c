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

#include <stdlib.h>
#include <ncurses.h>
#include <mangala.h>

#include "board.h"

#define BX 25
#define BY 7

int main(void)
{
	const char *user = getenv("USER");
	const char *enemy = "ENEMY";
	WINDOW *lboard, *rboard;
	WINDOW *bottom;
	struct mgl_game game;
	int ch;
	int maxx;

	mgl_initgame(&game);
	initscr();
	noecho();
	curs_set(0);

	maxx = getmaxx(stdscr);

	refresh();
	lboard = newwin(BY, BX, 5, 5);
	rboard = newwin(BY, BX, 5, 35);
	bottom = newwin(4, maxx, 13, 3);

	initboard(lboard);
	initboard(rboard);
	fillboard(lboard, game.board[1], game.board[0]);
	fillboard(rboard, game.board[0], game.board[1]);
	wrefresh(lboard);
	wrefresh(rboard);

	mvwaddstr(bottom, 0, 0, "press a number between 1 and 6");
	wrefresh(bottom);

	while ((ch = getch()) != 'q') {
		switch (ch) {
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
			ch -= 48;

			if (mgl_playturn(&game, ch-1) == MGL_ERR)
				goto warn;
			if (mgl_endgame(&game) == MGL_GAME_END)
				endofgame(&game, bottom, user, enemy);

			wmove(bottom, 1, 0);
			wclrtoeol(bottom);
			break;
		default:
		warn:
			mvwaddstr(bottom, 1, 0, "invalid selection. try again");
			break;
		}

		mvwprintw(bottom, 3, 0, "turn at user %s", game.user == game.board[0] ? user : enemy);
		wclrtoeol(bottom);

		/* and then redrawing of board window */
		fillboard(lboard, game.board[1], game.board[0]);
		fillboard(rboard, game.board[0], game.board[1]);
		wrefresh(lboard);
		wrefresh(rboard);
		wrefresh(bottom);
	}

	endwin();
}
