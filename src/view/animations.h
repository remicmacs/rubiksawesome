/**
 * @file animations.h
 * Defines the structures and functions to manage animations
 */


 #ifndef ANIMATIONS_H
 #define ANIMATIONS_H


#include <stdbool.h>
#include "graphics.h"


/**
 * A structure for the animations. Must be implemented in a separate
 * animation.h file later
 */
typedef struct _animation {
  bool isActive;
  bool ccw;
  int targetStep;
  int currentStep;
  int sliceIndex;
  enum FaceType animatedFace;
  struct _animation * next;
  void (* update)(struct _animation * self, rubikcube * rubikCube);
} animation;

animation * generateAnimation(int nbStep, enum FaceType animatedFace, int sliceIndex, bool ccw);
void addAnimation(animation ** animations, animation * toAdd);
void removeAnimation(animation ** animations, animation * toRemove);
void updateAnimationList(animation ** animations);

void animateX(animation * self, rubikcube * rubikCube);
void animateY(animation * self, rubikcube * rubikCube);
void animateZ(animation * self, rubikcube * rubikCube);

#endif
