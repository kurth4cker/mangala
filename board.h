#ifndef BOARD_H
#define BOARD_H
#include <stdint.h>
#include <ncurses.h>
#include <mangala.h>

/* print game finishing information to given WINDOW object. */
void endofgame(const struct mgl_game *, WINDOW *, const char *, const char *);

/* fill the WINDOW with given numbers */
void fillboard(WINDOW *, const int *, const int *);

/* initialize the board
 * draws the board windows internal borders */
void initboard(WINDOW *);

#endif /* BOARD_H */
