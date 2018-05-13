/**
 * @file graphics.h
 * Defines the structure for representing and generating the cubes; and the
 * functions for drawing and modifying the cubes.
 */


#ifndef GRAPHICS_H
#define GRAPHICS_H


#include <stdbool.h>


#define PI 3.141592653589793


/**
 * A structure to define colours
 */
typedef struct _colour {
  int r;  /**< The red channel */
  int g;  /**< The green channel */
  int b;  /**< The blue channel */
} colour;


/**
 * A structure holding 3 floats, used for the position, the rotation, the scale
 * and much more
 */
typedef struct _vector3 {
  float x;
  float y;
  float z;
} vector3;


/**
 * A structure representing a face. It is made of a colour and 4 corners
 */
typedef struct _face {
  vector3 corners[4]; /**< The list of corners. Each corner is a vector
                           representing the position of the corner */
  colour faceColour;  /**< The colour of the face */
} face;


/**
 * A structure holding the position, the rotation and the scale of an object.
 * All three are represented as vectors.
 */
typedef struct _transform {
  vector3 position; /**< The object's position */
  vector3 rotation; /**< The object's rotation */
  vector3 scale;    /**< The object's scale */
} transform;


/**
 * A structure for a simple cube. It holds 6 faces and a transform structure.
 */
typedef struct _cube {
  face faces[6];            /**< The faces of the cube */
  transform cubeTransform;  /**< The position, rotation and scale of the cube */
} cube;


/**
 * Not used yet.
 */
enum faceType {
  TOP,
  BOTTOM,
  FRONT,
  BACK,
  RIGHT,
  LEFT
};


/**
 * Generate a cube
 * @param  cubeTransform A transform structure holding the starting position,
 *                       rotation and scale
 * @return               A cube structure
 */
cube generateCube(transform cubeTransform);


/**
 * Set the colour of a cube
 * @param newColour    The colour we want to apply
 * @param selectedCube A pointer to the cube
 */
void setCubeColour(colour newColour, cube * selectedCube);


/**
 * Draw a cube on the screen
 * @param drawnCube The cube we will draw
 * @param debug     true to display the cube in magenta
 */
void drawCube(cube drawnCube, bool debug);


/**
 * Draw a face (basically a quad). Used by drawCube.
 * @param drawnFace The face to be drawn
 * @param position  The position of the face
 * @param rotation  The rotation of the face
 * @param scale     The scale of the face
 * @param debug     true to display the face in magenta
 */
void drawFace(face drawnFace, vector3 position, vector3 rotation, vector3 scale, bool debug);

#endif
