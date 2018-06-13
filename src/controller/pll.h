#ifndef PLL
#define PLL

#include <stdio.h>
#include <string.h>
#include "../model/cubelet.h"
#include "commandParser.h"
#include "debugController.h"
#include "patternComparator.h"
#include "f2l.h"
#include <stdbool.h>
#include <unistd.h>
#include "utils.h"

int isLastLayerEdgePlaced(cube *self);
char *placeEdgesLastLayer(cube *self);

bool isCubeDone(cube *self);
char *orientCornersLastLayer(cube *self);
bool isCorrectPosition(cube *self);
void *inverseEdges(cube *self);

#endif

