CC=gcc
CFLAGS =-Wall-Werror
all: src
src: main.o 
$(CC)$(CFLAGS) -o src main.o 

main.o: main.c
$(CC)$(CFLAG) -c main.c
clean:
rm -f src *.o
