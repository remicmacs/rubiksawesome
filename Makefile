CC = gcc
CFLAGS = -c -Wall -pedantic -Wextra
LIBS = -lSDL -lSDL_image -lGL -lGLU -lm

all: rubiksawesome

rubiksawesome: main.o graphics.o view.o animations.o
	$(CC) $(LIBS) main.o graphics.o view.o animations.o -o rubiksawesome

main.o: main.c
	$(CC) $(CFLAGS) main.c

graphics.o: src/view/graphics.c
	$(CC) $(CFLAGS) src/view/graphics.c

view.o: src/view/view.c
	$(CC) $(CFLAGS) src/view/view.c

animations.o: src/view/animations.c
	$(CC) $(CFLAGS) src/view/animations.c

clean:
	-rm *.o
