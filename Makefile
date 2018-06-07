CC = gcc
CFLAGS = -c -Wall -pedantic -Wextra
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lGL -lGLU -lm

all: rubiksawesome

rubiksawesome: main.o graphics.o view.o animations.o commandQueue.o debugController.o utils.o cube.o patternComparator.o errorController.o history.o commandParser.o arguments.o solver.o
	$(CC) $(LIBS) main.o graphics.o view.o animations.o commandQueue.o debugController.o utils.o cube.o patternComparator.o errorController.o history.o commandParser.o arguments.o  solver.o -o rubiksawesome

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

debugController.o: src/controller/debugController.c
	$(CC) $(CFLAGS) src/controller/debugController.c

errorController.o: src/controller/errorController.c
	$(CC) $(CFLAGS) src/controller/errorController.c

utils.o: src/controller/utils.c
	$(CC) $(CFLAGS) src/controller/utils.c

cube.o: src/model/cube.c
	$(CC) $(CFLAGS) src/model/cube.c

patternComparator.o: src/controller/patternComparator.c
	$(CC) $(CFLAGS) src/controller/patternComparator.c

history.o: src/controller/history.c
	$(CC) $(CFLAGS) src/controller/history.c

commandParser.o: src/controller/commandParser.c
	$(CC) $(CFLAGS) src/controller/commandParser.c

arguments.o : src/controller/arguments.c
	$(CC) $(CFLAGS) src/controller/arguments.c

solver.o : src/controller/solver.c
	$(CC) $(CFLAGS) src/controller/solver.c


clean:
	-rm *.o
