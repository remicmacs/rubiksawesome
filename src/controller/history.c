#include "history.h"

mvstack addCmdToHistory(mvstack history, move cmd) {
    push(history, cmd);
    return history;
}

move lastCommand(mvstack history) {
    move lastMove = pop(history);
    addCmdToHistory(history, lastMove);
    return lastMove;
}

move popCmd(mvstack history) {
    return pop(history);
}

void clearHistory(mvstack history) {
    while((int) popCmd(history) != -1);
}
