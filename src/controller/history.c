#include "history.h"

mvstack addCmdToHistory(mvstack history, move cmd) {
    if (!history) exitFatal("in addCmdToHistory(), history uninitialized");
    push(history, cmd);
    return history;
}

move lastCommand(mvstack history) {
    if (!history) exitFatal("in addCmdToHistory(), history uninitialized");
    move lastMove = pop(history);
    addCmdToHistory(history, lastMove);
    return lastMove;
}

move popCmd(mvstack history) {
    if (!history) exitFatal("in addCmdToHistory(), history uninitialized");
    return pop(history);
}

void clearHistory(mvstack history) {
    if (!history) exitFatal("in addCmdToHistory(), history uninitialized");
    while((int) popCmd(history) != -1);
}

void cancelMove(cube * cubeData, rubikview * mainView, mvstack history) {
    move cancelCmd = inverseMove(pop(history));
    cubeData->rotate(cubeData, cancelCmd);
    mainView->animate(mainView, cancelCmd, false);
    return;
}
