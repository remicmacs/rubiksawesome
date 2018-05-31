#include "src/view/view.h"
#include "src/controller/commandQueue.h"
#include "src/model/cube.h"
#include "src/controller/history.h"
#include "src/controller/arguments.h"
#include "src/controller/solver.h"

int main(int argc, char **argv) {
    srand(time(NULL));                      // Seeding random command
    mode gameMode = argParsing(argc, argv); // Identify game mode

    // Initializing data and graphic environment
    setWindow();
    rubikview mainView = generateView();
    mvqueue moveQueue = initQueue();
    mvstack moveStack = initQueue();
    cube * cubeData = initCube();
    // Scramble (or not) and saving init sequence for dev purposes
    move * initSequence = initGame(cubeData, &mainView, gameMode, argv);
     while (1) { // Main loop
    mainView.update(&mainView, moveQueue, moveStack);

    if (!isEmpty(moveQueue)) {
      move newMove = dequeue(moveQueue);
      if (newMove == RETURN) {
        if (!isEmpty(moveStack)) {
          cancelMove(cubeData, &mainView, moveStack);
        }
      } else if (newMove == RESTART) {
        mainView = generateView();
        moveQueue = initQueue();
        moveStack = initQueue();
        cubeData = initCube();
      } else if (newMove == SOLVE_PLS) {
          move * winSequence = fakeSolve(initSequence, moveStack);

          // TEMPORARY DISPLAY
          int index = -1;
          move aMove = (move)-1;
          fprintf(stderr, "Solving sequence : \n");
          while((int) (aMove = winSequence[++index]) != -1) {
            fprintf(stderr, "[%s]", mapMoveToCode(aMove));
          }
          fprintf(stderr, "\n");
      } else {
        mainView.animate(&mainView, newMove, false);
        cubeData->rotate(cubeData, newMove);
        cubeData->print(cubeData);
        addCmdToHistory(moveStack, newMove);
      }
    }
  }

  closeWindow(); // lol
  return 0;
}
