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
	struct mgl_game *game = (struct mgl_game *)malloc(sizeof(struct mgl_game));
	WINDOW *board;
	WINDOW *msgbox;
	int ch;

	mgl_initgame(game);
	initscr();
	noecho();
	curs_set(0);

	refresh();

	board = newwin(BY, BX, 0, 0);
	initboard(board);
	fillboard(board, game->board[1], game->board[0]);
	wrefresh(board);

	msgbox = newwin(4, getmaxx(stdscr), BY, 0);
	mvwaddstr(msgbox, 0, 0, "press a number between 1 and 6");
	wrefresh(msgbox);

	while ((ch = getch()) != 'q') {
		if (game->user)
			while (mgl_playturn(game, rand() % 6) != MGL_OK)
				;
		else
			switch (ch) {
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
				ch -= '0';

				mgl_playturn(game, ch-1);

				wmove(msgbox, 1, 0);
				wclrtoeol(msgbox);
				break;
			default:
				mvwaddstr(msgbox, 1, 0, "invalid selection. try again");
				break;
			}

		mvwprintw(msgbox, 3, 0, "turn at %s", game->user ? enemy : user);
		wclrtoeol(msgbox);

		if (mgl_endgame(game) == MGL_GAME_END)
			endofgame(game, msgbox, user, enemy);

		/* and then redrawing of board window */
		fillboard(board, game->board[1], game->board[0]);
		wrefresh(board);
		wrefresh(msgbox);
	}

	endwin();
	free(game);
}
