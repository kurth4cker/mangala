.POSIX:

NAME = mangala
VERSION = 0.1

CC = cc

LDLIBS = -ltinfo -lncurses -lmangala

PROG = mangala
OBJ = mangala.o board.o
SRC = mangala.c board.c
INC = board.h
DISTFILES = COPYING Makefile $(SRC) $(INC)

all: $(PROG)
$(PROG): $(OBJ)
$(OBJ): $(INC)

clean:
	rm -f $(PROG) $(OBJ)

dist:
	mkdir -p $(NAME)-$(VERSION)
	cp $(DISTFILES) $(NAME)-$(VERSION)
	tar -cf $(NAME)-$(VERSION).tar $(NAME)-$(VERSION)
	rm -rf $(NAME)-$(VERSION)

.SUFFIXES: .c .o
.c.o:
	$(CC) -std=c99 $(CFLAGS) $(CPPFLAGS) -c $<
.o:
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
