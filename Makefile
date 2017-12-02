CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -pedantic -std=c99 -lSDL2 -lSDL2_image -lm

OBJ = src/vector/vector.o src/character/character.o src/character/move.o \
      src/map/map.o src/camera/camera.o src/character/move_enemies.o \
      src/main/main.o src/menu/menu.o
BIN = Silly-Dying-Larry

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(BIN)

clean:
	$(RM) $(BIN) $(OBJ)
