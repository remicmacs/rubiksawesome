#ifndef OLL
#define OLL

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



bool yellowCrossDone(cube *self);
bool yellowFaceDone(cube *self);

char * doYellowCross(cube *self);
char * orientYellowCorners(cube *self);

int findYellowPattern(cube *self, char * movements);

void crossAlgorithm(cube *self, char * movements, int nb);

#endif
