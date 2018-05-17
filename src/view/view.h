/**
 * @file view.h
 * Defines functions to display and manipulate the Rubik's cube
 */


#ifndef VIEW_H
#define VIEW_H


#include <stdbool.h>
#include "graphics.h"


/**
 * A structure holding the camera position and rotation
 */
typedef struct _camera {
  vector3 position;           /**< Position in the cartesian coordinates */
  vector3 angles;             /**< Position in the spherical coordinates */
} camera;


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


/**
 * A structure holding all the informations related to the view
 */
typedef struct _rubikview {
  camera mainCamera;          /**< The camera in the view */
  bool isMoving;              /**< Indicates if the cube is moving */
  animation cubeAnimation;    /**< Holds the current animation */
  bool animationsEnabled;     /**< Enables or disables animations */
  rubikcube * rubikCube;      /**< The Rubik's cube */
} rubikview;


/**
 * Creates and displays the window
 */
void setWindow();


/**
 * Generate a view structure with all the cubes already generated and set
 * to a completed Rubik's cube.
 * @return A view structure
 */
rubikview generateView();


/**
 * Redraw the view and handle events. This function must be called on every
 * frame.
 * @param mainView The structure holding the view
 */
void update(rubikview * mainView);


/**
 * Rotate the Up face
 * @param mainView The structure holding the view
 */
void rotateUp(rubikview * mainView);


/**
 * Rotate the Down face
 * @param mainView The structure holding the view
 */
void rotateDown(rubikview * mainView);


/**
 * Rotate the Left face
 * @param mainView The structure holding the view
 */
void rotateLeft(rubikview * mainView);


/**
 * Rotate the Right face
 * @param mainView The structure holding the view
 */
void rotateRight(rubikview * mainView);


/**
 * Rotate the y slice
 * @param mainView The structure holding the view
 */
void rotateMiddle(rubikview * mainView);


/**
 * Rotate the Front face
 * @param mainView The structure holding the view
 */
void rotateFront(rubikview * mainView);


/**
 * Rotate the Back face
 * @param mainView The structure holding the view
 */
void rotateBack(rubikview * mainView);

void animateUp(rubikview * mainView);
void animateDown(rubikview * mainView);
void animateLeft(rubikview * mainView);
void animateRight(rubikview * mainView);
void animateMiddle(rubikview * mainView);
void animateFront(rubikview * mainView);
void animateBack(rubikview * mainView);

void rotateDataX(rubikcube * rubikCube, int xIndex, bool ccw);
void rotateDataY(rubikcube * rubikCube, int yIndex, bool ccw);
void rotateDataZ(rubikcube * rubikCube, int zIndex, bool ccw);

/**
 * Close the window
 */
void closeWindow();

#endif
