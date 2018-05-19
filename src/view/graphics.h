/**
 * @file graphics.h
 * Defines the structure for representing and generating the cubes; and the
 * functions for drawing and modifying the cubes.
 */


#ifndef GRAPHICS_H
#define GRAPHICS_H


#include <stdbool.h>
#include <stdio.h>
#include <GL/gl.h>


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
  float x;  /**< Actually x or r (if using spherical coordinates) */
  float y;  /**< Actually y or theta (if using spherical coordinates) */
  float z;  /**< Actually z or phi (if using spherical coordinates) */
} vector3;


/**
 * A structure representing a face. It is made of a colour and 4 corners
 */
typedef struct _face {
  vector3 corners[4]; /**< The list of corners. Each corner is a vector
                           representing the position of a vertex */
  vector3 normal;
  colour faceColour;  /**< The colour of the face */
} face;


/**
 * A structure holding the position, the rotation and the scale of an object.
 * All three are represented as vectors.
 */
typedef struct _transform {
  vector3 position; /**< The object's position */
  vector3 delta;    /**< Position's delta */
  vector3 rotation; /**< The object's rotation */
  vector3 scale;    /**< The object's scale */
} transform;


/**
 * A structure for a simple cube. It holds 6 faces and a transform structure.
 */
typedef struct _cube3d {
  face faces[6];            /**< The faces of the cube */
  transform cubeTransform;  /**< The position, rotation and scale of the cube */
} cube3d;


/**
 * A structure for a rubik's cube
 */
typedef struct _rubikcube {
  cube3d **** cubes;        /**< A 3x3x3 matrix of pointers to cubes */
} rubikcube;


typedef struct _texture {
  GLuint id;
  GLuint ccwId;
  GLuint id2;
  GLuint ccwId2;
} texture;


typedef struct _image {
  vector3 corners[4]; /**< The list of corners. Each corner is a vector
                           representing the position of a vertex */
  vector3 normal;
  texture imageTexture;
} image;


/**
 * This enum is used to designate the face being built or animated
 */
enum FaceType {
  TOP,
  DOWN,
  FRONT,
  BACK,
  RIGHT,
  LEFT,
  MIDDLE
};


/**
 * Generate a rubikcube structure with everything (cubes and such)
 * @return A pointer to the newly created rubikcube
 */
rubikcube * generateRubikCube();


/**
 * Generate a cube
 * @param  cubeTransform A transform structure holding the starting position,
 *                       rotation and scale
 * @return               A cube structure
 */
cube3d generateCube(transform cubeTransform);

/**
 * [generateFace description]
 * @param  cubeTransform [description]
 * @param  faceType      [description]
 * @return               [description]
 */
face generateFace(transform cubeTransform, enum FaceType faceType);


void generateTexture(GLuint * textureId, const char * url);


void generateCubemapTexture(GLuint * textureId);


image generateInstructions(enum FaceType faceType);


/**
 * Set the colour of a cube
 * @param newColour    The colour we want to apply
 * @param selectedCube A pointer to the cube
 */
void setCubeColour(colour newColour, cube3d * selectedCube);


/**
 * Draw a cube on the screen
 * @param drawnCube The cube we will draw
 * @param debug     true to display the cube in magenta
 */
void drawCube(cube3d drawnCube, bool debug);


/**
 * Draw a face (basically a quad). Used by drawCube.
 * @param drawnFace The face to be drawn
 * @param debug     true to display the face in magenta
 */
void drawFace(face drawnFace, bool debug);


void drawInstruction(image drawnInstruction, bool ccw, bool two);


void drawSkybox(GLuint textureId);


/**
 * Apply a rotation on a face around the Y axis
 * @param currentFace The face to rotate
 * @param angle       The angle for the rotation
 * @param ccw         True to set the rotation to counterclockwise;
 */
void rotateFaceY(face * currentFace, float angle, bool ccw);


/**
 * Apply a rotation on a face around the Z axis
 * @param currentFace The face to rotate
 * @param angle       The angle for the rotation
 * @param ccw         True to set the rotation to counterclockwise;
 */
void rotateFaceZ(face * currentFace, float angle, bool ccw);


/**
 * Apply a rotation on a face around the X axis
 * @param currentFace The face to rotate
 * @param angle       The angle for the rotation
 * @param ccw         True to set the rotation to counterclockwise;
 */
void rotateFaceX(face * currentFace, float angle, bool ccw);

#endif
