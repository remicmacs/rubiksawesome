#ifndef HISTORY_H
#define HISTORY_H

#include "commandQueue.h"
#include "../model/cube.h"

mvstack addCmdToHistory(mvstack history, move cmd);

move lastCommand(mvstack history);

move popCmd(mvstack history);

void clearHistory(mvstack history);


#endif
