#ifndef BOARD_H
#define BOARD_H
#include <stdint.h>
#include <ncurses.h>
#include <mangala.h>

/* print game finishing information to given WINDOW object. */
void endofgame(mgl_game_t *, WINDOW *);

/* fill the WINDOW with given numbers */
void fillboard(WINDOW *, uint8_t[7], uint8_t[7]);

/* initialize the board
 * draws the board windows internal borders */
void initboard(WINDOW *);

#endif /* BOARD_H */
