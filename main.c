#include "src/view/view.h"
#include "src/controller/commandQueue.h"
#include "src/model/cube.h"
#include "src/controller/history.h"
#include "src/controller/arguments.h"
#include "src/controller/solver.h"
#include "src/controller/patternComparator.h"

int main(int argc, char **argv) {
    srand(time(NULL));                      // Seeding random command
    printf( "    _ _ _\n"
            "  /_/_/_/\\ \n"
            " /_/_/_/\\/\\\n"
            "/_/_/_/\\/\\/\\ \n"
            "\\_\\_\\_\\/\\/\\/ \n"
            " \\_\\_\\_\\/\\/ \n"
            "  \\_\\_\\_\\/ \nWELCOME TO RUBIKSAWESOME !!!\n");
    mode gameMode = argParsing(argc, argv); // Identify game mode

    // Initializing data and graphic environment
    setSDL();
    rubikview mainView = generateView();
    mvqueue moveQueue = initQueue();
    mvstack moveStack = initQueue();
    cube * cubeData = initCube();
    cube * finishedCube = initCube();
    // Scramble (or not) and saving init sequence for dev purposes
    move * initSequence = initGame(cubeData, &mainView, gameMode, argv);

    // Solving sequence
    mvqueue solveQueue = initQueue();
    move * winSequence = (move *)malloc(sizeof(move));
    *winSequence = (move)-1;

     while (1) { // Main loop
    mainView.update(&mainView, moveQueue, moveStack, solveQueue);

    if (!isEmpty(moveQueue)) {
      move newMove = dequeue(moveQueue);
      if (newMove == *(head(solveQueue, 1))) {
          pop(solveQueue);
          mainView.animate(&mainView, newMove, false);
          cubeData->rotate(cubeData, newMove);
          cubeData->print(cubeData);
          if (patternMatches(cubeData, finishedCube)) {
              playWinningSequence(&mainView);
          }
      } else {
        if (newMove == RETURN) {
          if (!isEmpty(moveStack)) {
            pop(solveQueue);
            cancelMove(cubeData, &mainView, moveStack);
          }
        } else if (newMove == RESTART) {
          destroyCube(cubeData);
          freeQueue(moveQueue);
          freeQueue(moveStack);
          resetView(&mainView);
          moveQueue = initQueue();
          moveStack = initQueue();
          cubeData = initCube();

          // Reinitialize the game with the same game mode as at start
          free(initSequence);
          initSequence = initGame(cubeData, &mainView, gameMode, argv);
        } else if (newMove == SOLVE_PLS) {

            /* Let's call the solver */
            //winSequence = expandCommand(fakeSolve(initSequence, moveStack));
            winSequence = trueSolve(cubeData);
            printf("Cube solved: \n");
              printMoveArray(winSequence);
            /* We store it in a queue for the view */
            solveQueue = toMvQueue(winSequence);

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
          push(solveQueue, inverseMove(newMove));
          if (patternMatches(cubeData, finishedCube)) {
              playWinningSequence(&mainView);
          }
        }
      }
    }
  }

  closeWindow();
  return 0;
}
