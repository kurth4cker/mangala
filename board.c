#include <ncurses.h>

#include "board.h"

void
fillboard(WINDOW *win, int board[2][7])
{
	int i;

	for (i = 0; i < 6; i++) {
		mvwprintw(win, 5, 3 * i + 4, "%2d", board[0][i]);
		mvwprintw(win, 1, 23 - (3 * i + 4), "%2d", board[1][i]);
	}

	mvwprintw(win, 3, 1, "%2d", board[1][6]);
	mvwprintw(win, 3, 22, "%2d", board[0][6]);
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

	for (i = 3; i < 24; i += 18)
		mvwaddch(win, 3, i, ACS_VLINE);
	for (i = 2; i < 6; i += 2) {
		mvwaddch(win, i, 3, ACS_LTEE);
		mvwaddch(win, i, 21, ACS_RTEE);
	}
}
