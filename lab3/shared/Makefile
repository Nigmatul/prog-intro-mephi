CC=gcc
CFLAGS= -Werror -Wall -Wextra -pedantic -ftrapv
LDFLAGS= -L. -l:libarray.so -l:libmy.so
all: build clean
build:
	$(CC) -c main.c -o main.o
	$(CC) -c -fPIC libmy.c -o libmy.o $(CFLAGS)
	$(CC) -c -fPIC libarray.c -o libarray.o $(CFLAGS)
	gcc -shared libmy.o -o libmy.so
	gcc -shared libarray.o -o libarray.so
	$(CC) main.o $(LDFLAGS) -o lab3_dynamic
clean:
	rm -rf *.a
	rm -rf *.o
