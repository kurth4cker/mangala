#ifndef BOARD_H
#define BOARD_H
#include <stdint.h>
#include <ncurses.h>

/* fill the WINDOW with given numbers */
void fillboard(WINDOW *, uint8_t[2][7]);

/* initialize the board
 * draws the board windows internal borders */
void initboard(WINDOW *);

#endif /* BOARD_H */
