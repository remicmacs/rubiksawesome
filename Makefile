CC = gcc
CFLAGS = -c -Wall -pedantic -Wextra
LIBS = -lSDL -lSDL_image -lGL -lGLU -lm

all: rubiksawesome

rubiksawesome: main.o graphics.o view.o animations.o commandQueue.o debugController.o utils.o cube.o patternComparator.o errorController.o history.o
	$(CC) $(LIBS) main.o graphics.o view.o animations.o commandQueue.o debugController.o utils.o cube.o patternComparator.o errorController.o history.o -o rubiksawesome

main.o: main.c
	$(CC) $(CFLAGS) main.c

graphics.o: src/view/graphics.c
	$(CC) $(CFLAGS) src/view/graphics.c

view.o: src/view/view.c
	$(CC) $(CFLAGS) src/view/view.c

animations.o: src/view/animations.c
	$(CC) $(CFLAGS) src/view/animations.c

commandQueue.o: src/controller/commandQueue.c
	$(CC) $(CFLAGS) src/controller/commandQueue.c

debugController.o: src/controller/debugController.o
	$(CC) $(CFLAGS) src/controller/debugController.c

errorController.o: src/controller/errorController.o
	$(CC) $(CFLAGS) src/controller/errorController.c

utils.o: src/controller/utils.o
	$(CC) $(CFLAGS) src/controller/utils.c

cube.o: src/model/cube.o
	$(CC) $(CFLAGS) src/model/cube.c

patternComparator.o: src/controller/patternComparator.o
	$(CC) $(CFLAGS) src/controller/patternComparator.c

history.o: src/controller/history.o
	$(CC) $(CFLAGS) src/controller/history.c

clean:
	-rm *.o
