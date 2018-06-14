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
#include "graphics.h"


/**
 * A structure to hold all the informations relative to an animation. Can also
 * be used as a list.
 */
typedef struct _animation {
  bool isActive;              /**< True if the animation isn't finished */
  bool ccw;                   /**< True for a counterclockwise animation */
  int targetStep;             /**< The number of step (frames) to animate */
  int currentStep;            /**< The current step number */
  int sliceIndex;             /**< The index of the slice to be animated */
  float rotationAngle;        /**< The angle of rotation for each frame */
  enum FaceType animatedFace; /**< The type of the face to be animated */
  struct _animation * next;   /**< A pointer to the next animation */
  void (* update)(struct _animation * self, rubikcube * rubikCube);
  void (* onFinished)(rubikcube * cube, int sliceIndex, bool ccw);
} animation;


/**
 * A structure to hold animations and that will be used to execute groups
 * of animations serially. Is also a list.
 */
typedef struct _animationStack {
  animation * animations;         /**< A list of animations */
  Mix_Chunk * sound;              /**< The sound that will be played on start */
  bool hasStarted;                /**< True if the stack has been started */
  bool isFinished;                /**< True if the stack is finished */
  struct _animationStack * next;  /**< The next animation stack (for lists) */
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


/**
 * Remove an animation stack from a list of stack
 * @param animStack A pointer to the list of stacks
 * @param toRemove  The stack to be removed
 */
void removeAnimationStack(animationStack ** animStack, animationStack * toRemove);


/**
 * Count the number of stacks in a list
 * @param  animStack A pointer to the list of stacks
 * @return           The number of stacks in the list
 */
int animationStackCount(animationStack * animStack);


/**
 * Update an animation stack. Basically, it loops between all the animations
 * launch their update function
 * @param self      The
 * @param rubikCube [description]
 */
void updateAnimationStack(animationStack * self, rubikcube * rubikCube);


/**
 * Generate a new animation
 * @param  animatedFace The type of face to be animated
 * @param  sliceIndex   Index of the slice to be animated
 * @param  increment    Angle increment for the animation
 * @param  ccw          True to animate counterclockwise
 * @param  onFinished   Callback for when the animation is over
 * @return              A new animation
 */
animation * generateAnimation(enum FaceType animatedFace, int sliceIndex, float increment, bool ccw, void (* onFinished)(rubikcube * cube, int sliceIndex, bool ccw));


/**
 * Add an animation to a list of animations
 * @param animations The pointer to the list of animations
 * @param toAdd      The animation to add to the list
 */
void addAnimation(animation ** animations, animation * toAdd);


/**
 * Remove an animation from a list of animations
 * @param animations The pointer to the list of animations
 * @param toRemove   The animation to remove from the list
 */
void removeAnimation(animation ** animations, animation * toRemove);


/**
 * Update the animation list. It goes through all the animations and remove
 * the ones that are finished.
 * @param animations A pointer to the list of animations
 */
void updateAnimationList(animation ** animations);


/**
 * Animate a rotation around the X axis
 * @param self      The animation itself
 * @param rubikCube The rubikcube to animate
 */
void animateX(animation * self, rubikcube * rubikCube);


/**
 * Animate a rotation around the Y axis
 * @param self      The animation itself
 * @param rubikCube The rubikcube to animate
 */
void animateY(animation * self, rubikcube * rubikCube);


/**
 * Animate a rotation around the Z axis
 * @param self      The animation itself
 * @param rubikCube The rubikcube to animate
 */
void animateZ(animation * self, rubikcube * rubikCube);


/**
 * Start an animation stack
 * @param self  The animationstack itself
 * @param sound [description]
 */
void start(animationStack * self, Mix_Chunk * sound);

#endif
