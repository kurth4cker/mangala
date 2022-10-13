.POSIX:
CC = cc
LINK.c = $(CC) $(FLAGS) -o $@ $<

FLAGS = -std=c99 $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
BOARDLIBS = -ltinfo -lncurses

PROG = mangala board

all: $(PROG)
board: board.c
	$(LINK.c) $(BOARDLIBS) $(LDLIBS)

clean:
	rm -f $(PROG)

.SUFFIXES: .c
.c:
	$(LINK.c) $(LDLIBS)
