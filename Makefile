CC=gcc
CFLAGS=-g -Wall -Wextra -Werror -pedantic -std=c99 -lSDL2 -lSDL2_image

OBJ=src/vector/vector.o src/character/character.o src/character/move.o \
src/map/map.o src/camera/camera.o src/main/main.o

Silly-Dying-Larry: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o Silly-Dying-Larry

clean:
	$(RM) Silly-Dying-Larry *.o
