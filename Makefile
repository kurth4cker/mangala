.POSIX:
CC = cc

LDLIBS = -lmangala

PROG = mangala

all: $(PROG)
clean:
	rm -f $(PROG)

.SUFFIXES: .c
.c:
	$(CC) -std=c99 $(CFLAGS) $(CPPFLAGS) $< $(LDLIBS) -o $@
