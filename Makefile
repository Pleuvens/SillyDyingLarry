CC=gcc
CFLAGS=-g -Wall -Wextra -Werror -pedantic -std=c99 -lSDL2 -lSDL2_image

OBJ=src/main/main.c

rush-c:
	$(CC) $(CFLAGS) $(OBJ) -o rush-c

clean:
	$(RM) rush-c *.o
