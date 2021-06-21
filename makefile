CC = gcc
CFLAGS = -std=gnu99 -g -Wpedantic

all: drawDir

drawDir.o: drawDir.c
	$(CC) $(CFLAGS) -c drawDir.c -o drawDir.o

drawDir: drawDir.o drawDir.c
	$(CC) $(CFLAGS) -o drawDir drawDir.o

clean:
	rm *.o drawDir