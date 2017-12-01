CC=gcc
CFLAGS=-g -Wall -Wextra -Werror -pedantic -std=c99 -lSDL2 -lSDL2_image

OBJ=src/map/map.c src/main/main.c

Silly-Dying-Larry:
	$(CC) $(CFLAGS) $(OBJ) -o Silly-Dying-Larry

clean:
	$(RM) Silly-Dying-Larry *.o
