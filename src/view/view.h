/**
 * @file view.h
 * Defines functions to display and manipulate the Rubik's cube
 */


#ifndef VIEW_H
#define VIEW_H


#include <stdbool.h>
#include <GL/gl.h>
#include "graphics.h"
#include "animations.h"


#define PI_DENOMINATOR 90
#define ROTATION_ANGLE (PI / PI_DENOMINATOR)
#define ANIMATIONS_STEP (PI_DENOMINATOR / 2)


/**
 * A structure holding the camera position and rotation
 */
typedef struct _camera {
  vector3 position;           /**< Position in the cartesian coordinates */
  vector3 angles;             /**< Position in the spherical coordinates */
} camera;


/**
 * A structure holding all the informations related to the view
 */
typedef struct _rubikview {
  camera mainCamera;          /**< The camera in the view */
  rubikcube * rubikCube;      /**< The Rubik's cube */
  animation * animations;
  GLuint texture;
  image instructions[6];
  void (* update)(struct _rubikview * mainView);
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

void rotateDataX(rubikcube * rubikCube, int xIndex, bool ccw);
void rotateDataY(rubikcube * rubikCube, int yIndex, bool ccw);
void rotateDataZ(rubikcube * rubikCube, int zIndex, bool ccw);

/**
 * Close the window
 */
void closeWindow();

#endif
