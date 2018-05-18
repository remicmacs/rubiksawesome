/**
 * @file animations.c
 */


#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "graphics.h"
#include "view.h"
#include "animations.h"


animation * generateAnimation(int nbStep, enum FaceType animatedFace, int sliceIndex, bool ccw) {
  animation * returnedAnimation;
  returnedAnimation = (animation *)malloc(sizeof(animation));

  returnedAnimation->currentStep = 0;
  returnedAnimation->targetStep = nbStep;
  returnedAnimation->animatedFace = animatedFace;
  returnedAnimation->isActive = false;
  returnedAnimation->sliceIndex = sliceIndex;
  returnedAnimation->next = NULL;
  returnedAnimation->ccw = ccw;

  switch(animatedFace) {
    case TOP:
    case DOWN:
      returnedAnimation->update = &animateZ;
      break;
    case RIGHT:
    case LEFT:
    case MIDDLE:
      returnedAnimation->update = &animateX;
      break;
    case FRONT:
    case BACK:
      returnedAnimation->update = &animateY;
      break;
  }

  return returnedAnimation;
}


void addAnimation(animation ** animations, animation * toAdd) {
  animation * currentAnimation = *animations;
  if (currentAnimation == NULL) {
    *animations = toAdd;
  } else {
    while (currentAnimation->next != NULL) {
      currentAnimation = currentAnimation->next;
    }
    currentAnimation->next = toAdd;
  }
  toAdd->isActive = true;
}


void removeAnimation(animation ** animations, animation * toRemove) {
  animation * currentAnimation = *animations;
  if (currentAnimation == toRemove) {
    *animations = NULL;
  }
  while (currentAnimation != NULL) {
    if (currentAnimation->next == toRemove) {
      currentAnimation->next = toRemove->next;
      free(toRemove);
      break;
    }
    currentAnimation = currentAnimation->next;
  }
}


void updateAnimationList(animation ** animations) {
  animation * currentAnimation = *animations;
  while (currentAnimation != NULL) {
    if (!currentAnimation->isActive) {
      removeAnimation(animations, currentAnimation);
    }
    currentAnimation = currentAnimation->next;
  }
}


void animateX(animation * self, rubikcube * rubikCube) {
  if (self->currentStep == self->targetStep) {
    self->isActive = false;
    rotateDataX(rubikCube, self->sliceIndex, self->ccw);
  } else {
    for (int xIndex = 0; xIndex < 3; xIndex++) {
      for (int yIndex = 0; yIndex < 3; yIndex++) {
        for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
          rotateFaceX(&rubikCube->cubes[self->sliceIndex][xIndex][yIndex]->faces[faceIndex], ROTATION_ANGLE, self->ccw);
        }
      }
    }
    self->currentStep++;
  }
}


void animateY(animation * self, rubikcube * rubikCube) {
  if (self->currentStep == self->targetStep) {
    self->isActive = false;
    rotateDataY(rubikCube, self->sliceIndex, self->ccw);
  } else {
    for (int xIndex = 0; xIndex < 3; xIndex++) {
      for (int yIndex = 0; yIndex < 3; yIndex++) {
        for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
          rotateFaceY(&rubikCube->cubes[xIndex][self->sliceIndex][yIndex]->faces[faceIndex], ROTATION_ANGLE, self->ccw);
        }
      }
    }
    self->currentStep++;
  }
}


void animateZ(animation * self, rubikcube * rubikCube) {
  if (self->currentStep == self->targetStep) {
    self->isActive = false;
    rotateDataZ(rubikCube, self->sliceIndex, self->ccw);
  } else {
    for (int xIndex = 0; xIndex < 3; xIndex++) {
      for (int yIndex = 0; yIndex < 3; yIndex++) {
        for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
          rotateFaceZ(&rubikCube->cubes[xIndex][yIndex][self->sliceIndex]->faces[faceIndex], ROTATION_ANGLE, self->ccw);
        }
      }
    }
    self->currentStep++;
  }
}
