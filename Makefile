CC=gcc
CFLAGS=-Wall -std=c99 -g
DEPS=
LIBOBJS=bencode.o
TESTOBJS=bencode-test.o
PROGOBJS=bt.o

all: bencode-test bt

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

bencode-test: $(LIBOBJS) $(TESTOBJS) bencode.h
	$(CC) $(CFLAGS) -o $@ $(LIBOBJS) $(TESTOBJS)

bt: $(LIBOBJS) $(PROGOBJS)
	$(CC) $(CFLAGS) -o $@ $(LIBOBJS) $(PROGOBJS)

.PHONY: clean

clean:
	rm -f *.o *.c~
	-rm -f bencode-test bt
test: bencode-test
	./bencode-test

leakcheck: bencode-test
	valgrind --leak-check=yes ./bencode-test
