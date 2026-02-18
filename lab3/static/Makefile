CC=gcc
CFLAGS= -Werror -Wall -Wextra -pedantic -ftrapv
LDFLAGS= -L. -larray -lmy
all: build clean
build:
	$(CC) -c main.c -o main.o
	$(CC) -c libmy.c -o libmy.o $(CFLAGS)
	$(CC) -c libarray.c -o libarray.o $(CFLAGS)
	ar rcs libmy.a libmy.o
	ar rcs libarray.a libarray.o
	$(CC) main.o $(LDFLAGS) -o lab3_static
clean:
	rm -rf *.a
	rm -rf *.o
