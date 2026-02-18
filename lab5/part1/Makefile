CC=gcc
CFLAGS= -Werror -Wall -Wextra -pedantic -ftrapv -g
LDFLAGS= -L. -lvector -lsort -lio -lgen -ladditional
all: build clean
build:
	$(CC) -c main.c -o main.o $(CFLAGS)
	$(CC) -c vector.c -o libvector.o $(CFLAGS)
	$(CC) -c sort.c -o libsort.o $(CFLAGS)
	$(CC) -c io.c -o libio.o $(CFLAGS)
	$(CC) -c gen.c -o libgen.o $(CFLAGS)
	$(CC) -c additional.c -o libadditional.o $(CFLAGS)
	ar rcs libvector.a libvector.o
	ar rcs libsort.a libsort.o
	ar rcs libio.a libio.o
	ar rcs libgen.a libgen.o
	ar rcs libadditional.a libadditional.o
	$(CC) main.o $(LDFLAGS) -o lab5
clean:
	rm -rf *.a
	rm -rf *.o
