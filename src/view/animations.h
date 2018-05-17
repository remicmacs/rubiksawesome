/**
 * @file animations.h
 * Defines the structures and functions to manage animations
 */


 #ifndef ANIMATIONS_H
 #define ANIMATIONS_H


#include "graphics.h"


/**
 * A structure for the animations. Must be implemented in a separate
 * animation.h file later
 */
typedef struct _animation {
  bool isActive;
  int targetStep;
  int currentStep;
  enum FaceType animatedFace;
} animation;


#endif
