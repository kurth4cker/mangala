.POSIX:

NAME = mangala
VERSION = 0.1

CC = cc

MANGALA_LIBS = -lmangala
NCURSES_LIBS = -lncurses -ltinfo

MGL_CFLAGS = -std=c99 $(CFLAGS) -DPACKAGE_STRING='"$(NAME) $(VERSION)"' $(CPPFLAGS) $(MANGALA_CFLAGS) $(NCURSES_CFLAGS)
MGL_LDFLAGS = $(LDFLAGS) $(MANGALA_LDFLAGS) $(NCURSES_LDFLAGS)
MGL_LIBS = $(LDLIBS) $(MANGALA_LIBS) $(NCURSES_LIBS)

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
	$(CC) $(MGL_CFLAGS) -c $<
.o:
	$(CC) $(MGL_LDFLAGS) -o $@ $^ $(MGL_LIBS)
