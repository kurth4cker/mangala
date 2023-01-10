/* mangala.c --- complete mangala game implementation using libmangala
 *
 * Copyright 2022,2023 kurth4cker
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

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <mangala.h>

#include "board.h"

#define BX 25
#define BY 7

int main(int argc, char **argv)
{
	const char *user = getenv("USER");
	const char *enemy = "ENEMY";
	struct mgl_game game;
	WINDOW *board;
	WINDOW *msgbox;
	int ch;

	while ((ch = getopt(argc, argv, "u:e:hv")) != -1)
		switch (ch) {
		case 'u':
			user = optarg;
			break;
		case 'e':
			enemy = optarg;
			break;
		case 'h':
			puts("see mangala(1)");
			return 0;
		case 'v':
			puts(PACKAGE_STRING);
			return 0;
		case '?':
			return 1;
		}

	mgl_initgame(&game);
	initscr();
	noecho();
	curs_set(0);

	refresh();

	board = newwin(BY, BX, 0, 0);
	initboard(board);
	fillboard(board, game.board[1], game.board[0]);
	wrefresh(board);

	msgbox = newwin(4, getmaxx(stdscr), BY, 0);
	mvwaddstr(msgbox, 0, 0, "press a number between 1 and 6");
	wrefresh(msgbox);

	while ((ch = getch()) != 'q') {
		if (game.user)
			while (mgl_playturn(&game, rand() % 6) != MGL_OK)
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

				mgl_playturn(&game, ch-1);

				wmove(msgbox, 1, 0);
				wclrtoeol(msgbox);
				break;
			default:
				mvwaddstr(msgbox, 1, 0, "invalid selection. try again");
				break;
			}

		mvwprintw(msgbox, 3, 0, "turn at %s", game.user ? enemy : user);
		wclrtoeol(msgbox);

		if (mgl_endgame(&game) == MGL_GAME_END)
			endofgame(&game, msgbox, user, enemy);

		/* and then redrawing of board window */
		fillboard(board, game.board[1], game.board[0]);
		wrefresh(board);
		wrefresh(msgbox);
	}

	endwin();
}
