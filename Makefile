.POSIX:
CC = cc
LINK.c = $(CC) $(FLAGS) -o $@ $<

LDLIBS = -ltinfo -lncurses

PROG = mangala
OBJ = mangala.o board.o

all: $(PROG)
$(PROG): $(OBJ)
$(OBJ): board.h

clean:
	rm -f $(PROG) $(OBJ)

.SUFFIXES: .c .o
.c.o:
	$(CC) -std=c99 $(CFLAGS) $(CPPFLAGS) -c $<
.o:
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
