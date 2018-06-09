/**
 * @file animations.h
 * Defines the structures and functions to manage animations
 */


 #ifndef ANIMATIONS_H
 #define ANIMATIONS_H


#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL_mixer.h>
#include "view.h"
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
  float rotationAngle;
  enum FaceType animatedFace;
  struct _animation * next;
  void (* update)(struct _animation * self, rubikcube * rubikCube);
  void (* onFinished)(rubikcube * cube, int sliceIndex, bool ccw);
} animation;


typedef struct _animationStack {
  animation * animations;
  Mix_Chunk * sound;
  bool hasStarted;
  bool isFinished;
  struct _animationStack * next;
  void (* start)(struct _animationStack * self, Mix_Chunk * sound);
  void (* update)(struct _animationStack * self, rubikcube * rubikCube);
} animationStack;


/**
 * Generate an animation stack
 * @param  sound The sound it will play when it will activate
 * @return       A pointer to the new animation stack
 */
animationStack * generateAnimationStack(Mix_Chunk * sound);

/**
 * Add an animation stack to a list of stack
 * @param animStack A pointer to the list of stacks
 * @param toAdd     The animation stack to add to the list
 */
void addAnimationStack(animationStack ** animStack, animationStack * toAdd);
void removeAnimationStack(animationStack ** animStack, animationStack * toRemove);
int animationStackCount(animationStack * animStack);
void updateAnimationStack(animationStack * self, rubikcube * rubikCube);

animation * generateAnimation(enum FaceType animatedFace, int sliceIndex, float increment, bool ccw);
void addAnimation(animation ** animations, animation * toAdd);
void removeAnimation(animation ** animations, animation * toRemove);
void updateAnimationList(animation ** animations);

void animateX(animation * self, rubikcube * rubikCube);
void animateY(animation * self, rubikcube * rubikCube);
void animateZ(animation * self, rubikcube * rubikCube);

void start(animationStack * self, Mix_Chunk * sound);

#endif
