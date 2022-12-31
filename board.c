/* board.c --- ncurses related functions
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

void
endofgame(const struct mgl_game *game, WINDOW *win, const char *user, const char *enemy)
{
	const char *winner = game->board[0][6] > game->board[1][6] ? user : enemy;

	mvwaddstr(win, 0, 0, "GAME OVER");
	wclrtoeol(win);
	mvwprintw(win, 1, 0, "WINNER: %s", winner);
	wclrtoeol(win);
}

void
fillboard(WINDOW *win, const int *up, const int *bottom)
{
	int i;

	for (i = 0; i < 6; i++) {
		mvwprintw(win, 5, 3 * i + 4, "%2d", bottom[i]);
		mvwprintw(win, 1, 23 - (3 * i + 4), "%2d", up[i]);
	}

	mvwprintw(win, 3, 1, "%2d", up[6]);
	mvwprintw(win, 3, 22, "%2d", bottom[6]);
}

void
initboard(WINDOW *win)
{
	int i;

	box(win, 0, 0);

	for (i = 3; i < 24; i += 3) {
		mvwaddch(win, 0, i, ACS_TTEE);
		mvwaddch(win, 1, i, ACS_VLINE);
		mvwaddch(win, 2, i, ACS_BTEE);
		mvwaddch(win, 4, i, ACS_TTEE);
		mvwaddch(win, 5, i, ACS_VLINE);
		mvwaddch(win, 6, i, ACS_BTEE);
	}

	for (i = 4; i < 21; i += 3) {
		mvwaddch(win, 2, i, ACS_HLINE);
		waddch(win, ACS_HLINE);
		mvwaddch(win, 4, i, ACS_HLINE);
		waddch(win, ACS_HLINE);
	}

	mvwaddch(win, 3, 3, ACS_VLINE);
	mvwaddch(win, 3, 21, ACS_VLINE);

	for (i = 2; i < 6; i += 2) {
		mvwaddch(win, i, 3, ACS_LTEE);
		mvwaddch(win, i, 21, ACS_RTEE);
	}
}
