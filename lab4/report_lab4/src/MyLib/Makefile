CC=gcc
CFLAGS= -Wall -Wextra -pedantic -ftrapv -g
LDFLAGS= -L. -l:mystring.a -l:individual.a
all: build clean
build:
	$(CC) -c main.c -o main.o $(CFLAGS)
	$(CC) -c mystring.c -o mystring.o $(CFLAGS)
	$(CC) -c individual.c -o individual.o $(CFLAGS)
	ar rcs mystring.a mystring.o
	ar rcs individual.a individual.o
	$(CC) main.o $(LDFLAGS) -o lab4_myfunc
clean:
	rm -rf *.a
	rm -rf *.o
