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
#include "../model/cube.h"
#include "../controller/commandQueue.h"
//#include "../controller/history.h"


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
  animation * animations;     /**< A list of the animations */
  image instructions[6];      /**< An array of images for the instructions */
  textureStore texStore;
  bool instructionsDisplayed; /**< Set to true to show the instructions */
  bool gameWon;
  void (* update)(struct _rubikview * mainView, mvqueue moveQueue, mvstack moveStack);
  void (* animate)(struct _rubikview * self, move order, bool fast);
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
void update(rubikview * mainView, mvqueue moveQueue, mvstack moveStack);


/**
 * Rotate the data around the X axis
 * @param rubikCube The rubik's cube structure
 * @param xIndex    The index of the slice you want to rotate, on the X axis
 * @param ccw       Set to true for a counterclockwise rotation
 */
void rotateDataX(rubikcube * rubikCube, int xIndex, bool ccw);


/**
 * Rotate the data around the Y axis
 * @param rubikCube The rubik's cube structure
 * @param xIndex    The index of the slice you want to rotate, on the Y axis
 * @param ccw       Set to true for a counterclockwise rotation
 */
void rotateDataY(rubikcube * rubikCube, int yIndex, bool ccw);


/**
 * Rotate the data around the Z axis
 * @param rubikCube The rubik's cube structure
 * @param xIndex    The index of the slice you want to rotate, on the Z axis
 * @param ccw       Set to true for a counterclockwise rotation
 */
void rotateDataZ(rubikcube * rubikCube, int zIndex, bool ccw);


/**
 * Parse and order and animate the cube accordingly
 * @param mainView The rubikview structure (needed to access the data)
 * @param order    The order, a move structure from cube.h
 * @param fast     Set to true to disable animation and have instantaneous move
 */
void parseOrder(rubikview * mainView, move order, bool fast);


/**
 * Close the window
 */
void closeWindow();


#endif
