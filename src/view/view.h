/**
 * @file view.h
 * Defines functions to display and manipulate the Rubik's cube
 */


#ifndef VIEW_H
#define VIEW_H


#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "graphics.h"


/**
 * A structure holding the camera position and rotation
 */
typedef struct _camera {
  vector3 position;           /**< Position in the cartesian coordinates **/
  vector3 angles;             /**< Position in the spherical coordinates **/
} camera;


/**
 * A structure holding all the informations related to the view
 */
typedef struct _rubikview {
  camera mainCamera;          /**< The camera in the view **/
  cube * cubes;               /**< All the cubes composing the Rubik's cube **/
  cube * backFace[9];         /**< The cubes composing the back face **/
  cube * frontFace[9];        /**< The cubes composing the front face **/
  cube * rightFace[9];        /**< The cubes composing the right face **/
  cube * leftFace[9];         /**< The cubes composing the left face **/
  cube * bottomFace[9];       /**< The cubes composing the down face **/
  cube * topFace[9];          /**< The cubes composing the top face **/
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
 * Generates a list of 27 cubes representing all the cubes in a Rubik's cube
 * @return A pointer to the list of 3D cubes
 */
cube * generateCubes();


/**
 * Set the pointers in the faces to the corresponding cubes
 * @param mainView The structure holding the view
 */
void attachCubesToFaces(rubikview * mainView);


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
 * Rotate the Front face
 * @param mainView The structure holding the view
 */
void rotateFront(rubikview * mainView);


/**
 * Rotate the Back face
 * @param mainView The structure holding the view
 */
void rotateBack(rubikview * mainView);

/**
 * Close the window
 */
void closeWindow();

#endif
