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
	fillboard(board, game.board[1], game.board[0]);
	wrefresh(board);

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

			/* here are some turn initing or playing actions */
			if (mgl_initturn(&game, ch-1) == MGL_ERR)
				goto warn;
			mgl_playturn(&game);
			mgl_endturn(&game);
			if (mgl_endgame(&game) == MGL_GAME_END)
				endofgame(&game, bottom);
			break;
		default:
		warn:
			mvwaddstr(bottom, 1, 0, "invalid selection. try again");
			break;
		}

		mvwprintw(bottom, 3, 0, "turn at user %d", mgl_getuser(&game));
		/* and then redrawing of board window */
		fillboard(board, game.board[1], game.board[0]);
		wrefresh(board);
		wrefresh(bottom);
	}

	endwin();
}
