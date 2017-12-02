CC=gcc
CFLAGS=-g -Wall -Wextra -Werror -pedantic -std=c99 -lSDL2 -lSDL2_image

OBJ=src/vector/vector.c src/character/character.c src/character/move.c \
src/map/map.c src/camera/camera.c src/main/main.c

Silly-Dying-Larry:
	$(CC) $(CFLAGS) $(OBJ) -o Silly-Dying-Larry

clean:
	$(RM) Silly-Dying-Larry *.o
