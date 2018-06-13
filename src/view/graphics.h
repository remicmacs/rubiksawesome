/**
 * @file graphics.h
 * Defines the structure for representing and generating the cubes; and the
 * functions for drawing and modifying the cubes.
 */


#ifndef GRAPHICS_H
#define GRAPHICS_H


#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../model/cube.h"
#include "../controller/commandQueue.h"


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


typedef struct _instructionTextures {
  GLuint id;        /**< The ID for the base texture */
  GLuint ccwId;     /**< The ID for the inverted texture */
  GLuint id2;       /**< The ID for the double texture */
  GLuint ccwId2;    /**< The ID for the double inverted texture */
} instructionTextures;


typedef struct _instructionDisplay {
  vector3 corners[4];           /**< The list of corners. Each corner is a
                                vector representing the position of a vertex */
  vector3 normal;               /**< The normal vector of the face */
  instructionTextures textures; /**< The texture of the instruction */
} instructionDisplay;


typedef struct _historyDisplay {
  GLuint id;
  vector3 corners[4];
} historyDisplay;


typedef struct _texture {
  GLuint id;
  SDL_Surface * surface;
} texture;


typedef struct _textureStore {
  texture up;
  texture upi;
  texture upid;
  texture upd;

  texture down;
  texture downi;
  texture downid;
  texture downd;

  texture front;
  texture fronti;
  texture frontid;
  texture frontd;

  texture back;
  texture backi;
  texture backid;
  texture backd;

  texture right;
  texture righti;
  texture rightid;
  texture rightd;

  texture left;
  texture lefti;
  texture leftid;
  texture leftd;

  GLuint skybox;

  texture xyz;
  texture xyzi;

  texture x;
  texture xi;

  texture y;
  texture yi;

  texture z;
  texture zi;

  texture winner;
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
void generateTexture(texture * newTexture, const char * url);


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
instructionDisplay generateInstruction(enum FaceType faceType, textureStore texStore);


/**
 * Set the colour of a cube
 * @param newColour    The colour we want to apply
 * @param selectedCube A pointer to the cube
 */
void setCubeColour(colour newColour, cube3d * selectedCube);


void drawCubes(rubikcube * rubikCube);


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


void drawInstructions(instructionDisplay * instructions, int keyShortcut);


/**
 * Draw an instruction floating in front of a face
 * @param drawnInstruction The image structure for the instruction's image
 * @param ccw              Is the counterclockiwse modifier active ?
 * @param two              Is the double modifier active ?
 */
void drawInstruction(instructionDisplay drawnInstruction, int keyShortcut);


void drawXYZInstruction(textureStore texStore, bool reversed);


/**
 * Draw the skybox
 * @param textureId The ID of the skybox
 */
void drawSkybox(GLuint textureId);


void drawHistory(textureStore texStore, mvstack moveStack);


void drawWinning(textureStore texStore);


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


/**
 * Translate a move to a texture. Used to display history.
 * @param  texStore The structure where the textures are stored
 * @param  command  The move command
 * @return          The ID of the OpenGL's texture
 */
texture moveToTexture(textureStore texStore, move command);


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
