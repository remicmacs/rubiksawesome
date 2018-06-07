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
#include "../model/cube.h"


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
  vector3 normal;     /**< The normal vector of the face */
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
  GLuint id;        /**< The ID for the base texture */
  GLuint ccwId;     /**< The ID for the inverted texture */
  GLuint id2;       /**< The ID for the double texture */
  GLuint ccwId2;    /**< The ID for the double inverted texture */
} texture;


typedef struct _image {
  vector3 corners[4];   /**< The list of corners. Each corner is a vector
                           representing the position of a vertex */
  vector3 normal;       /**< The normal vector of the face */
  texture imageTexture; /**< The texture of the instruction */
} image;


typedef struct _historyDisplay {
  GLuint id;
  vector3 corners[4];
} historyDisplay;


typedef struct _textureStore {
  GLuint up;
  GLuint upi;
  GLuint upid;
  GLuint upd;

  GLuint down;
  GLuint downi;
  GLuint downid;
  GLuint downd;

  GLuint front;
  GLuint fronti;
  GLuint frontid;
  GLuint frontd;

  GLuint back;
  GLuint backi;
  GLuint backid;
  GLuint backd;

  GLuint right;
  GLuint righti;
  GLuint rightid;
  GLuint rightd;

  GLuint left;
  GLuint lefti;
  GLuint leftid;
  GLuint leftd;

  GLuint skybox;

  GLuint xyz;
  GLuint xyzi;

  GLuint x;
  GLuint xi;

  GLuint y;
  GLuint yi;

  GLuint z;
  GLuint zi;

  GLuint winner;
} textureStore;


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


/**
 * Generate a texture from an image
 * @param textureId The ID of the texture
 * @param url       The path to the image
 */
void generateTexture(GLuint * textureId, const char * url);


/**
 * Generate a cubemap texture
 * @param textureId The ID of the cubemap texture
 */
void generateCubemapTexture(GLuint * textureId);


/**
 * Generate the texture store
 * @return A texture store
 */
textureStore generateTextureStore();


/**
 * Generate an instruction's image
 * @param  faceType The face the instruction is attached to
 * @return          The image structure holding all the textures
 */
image generateInstruction(enum FaceType faceType, textureStore texStore);


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


/**
 * Draw an instruction floating in front of a face
 * @param drawnInstruction The image structure for the instruction's image
 * @param ccw              Is the counterclockiwse modifier active ?
 * @param two              Is the double modifier active ?
 */
void drawInstruction(image drawnInstruction, bool ccw, bool two);


/**
 * Draw the skybox
 * @param textureId The ID of the skybox
 */
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


GLuint moveToTexture(textureStore texStore, move command);

/**
 * Destroys the rubikcube
 *
 * Frees the memory of the rubikcube data structure and of nested data
 * structures inside it
 *
 * @param aCube - Pointer to the rubikcube data structure to free
 */
void destroyRubikCube(rubikcube * aCube);

#endif
