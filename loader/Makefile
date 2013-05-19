CC ?= gcc
CFLAGS ?= -O2 -Wall

loader: loader.c
	$(CC) $(CFLAGS) -s -o loader loader.c -lusb

clean:
	rm -f loader
