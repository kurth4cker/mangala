#include <stdio.h>

#include "board.h"

int
main()
{
	WINDOW *board;

	initscr();
	noecho();
	curs_set(0);

	refresh();
        board = newwin(7, 25, 5, 5);
	initboard(board);
	wrefresh(board);

	getch();
	endwin();
}
