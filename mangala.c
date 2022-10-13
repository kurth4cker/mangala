#include <stdio.h>

#include "board.h"

int
main()
{
	WINDOW *win;

	initscr();
	noecho();
	curs_set(0);

	refresh();
	win = newwin(7, 25, 5, 5);
	initboard(win);
	wrefresh(win);

	getch();
	endwin();
}
