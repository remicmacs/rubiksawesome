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


/**
 * A structure holding the ids of the OpenGL's textures for the instructions
 */
typedef struct _instructionTextures {
  GLuint id;        /**< The ID for the base texture */
  GLuint ccwId;     /**< The ID for the inverted texture */
  GLuint id2;       /**< The ID for the double texture */
  GLuint ccwId2;    /**< The ID for the double inverted texture */
} instructionTextures;


/**
 * A structure for the quad on which the instructions textures are displayed
 */
typedef struct _instructionDisplay {
  vector3 corners[4];           /**< The list of corners. Each corner is a
                                vector representing the position of a vertex */
  vector3 normal;               /**< The normal vector of the face */
  instructionTextures textures; /**< The texture of the instruction */
} instructionDisplay;


/**
 * A structure for the quad on which each history's element is displayed
 */
typedef struct _historyDisplay {
  GLuint id;            /**< The id of the OpenGL's texture */
  vector3 corners[4];   /**< The list of corners */
} historyDisplay;


/**
 * A structure holding the OpenGL's id and SDL's surface for a texture
 */
typedef struct _texture {
  GLuint id;              /**< Id of the OpenGL's texture */
  SDL_Surface * surface;  /**< The SDL surface of the texture */
} texture;


/**
 * A structure holding all the textures
 */
typedef struct _textureStore {
  texture up;         /**< The U instruction */
  texture upi;        /**< The Ui instruction */
  texture upid;       /**< The ui instruction */
  texture upd;        /**< The u instruction */

  texture down;       /**< The D instruction */
  texture downi;      /**< The Di instruction */
  texture downid;     /**< The di instruction */
  texture downd;      /**< The d instruction */

  texture front;      /**< The F instruction */
  texture fronti;     /**< The Fi instruction */
  texture frontid;    /**< The fi instruction */
  texture frontd;     /**< The f instruction */

  texture back;       /**< The B instruction */
  texture backi;      /**< The Bi instruction */
  texture backid;     /**< The bi instruction */
  texture backd;      /**< The b instruction */

  texture right;      /**< The R instruction */
  texture righti;     /**< The Ri instruction */
  texture rightid;    /**< The ri instruction */
  texture rightd;     /**< The r instruction */

  texture left;       /**< The L instruction */
  texture lefti;      /**< The Li instruction */
  texture leftid;     /**< The li instruction */
  texture leftd;      /**< The l instruction */

  GLuint skybox;      /**< The skybox's texture */

  texture xyz;        /**< The XYZ instruction */
  texture xyzi;       /**< The XYZi instruction */

  texture x;          /**< The X instruction */
  texture xi;         /**< The Xi instruction */

  texture y;          /**< The Y instruction */
  texture yi;         /**< The Yi instruction */

  texture z;          /**< The Z instruction */
  texture zi;         /**< The Zi instruction */

  texture winner;     /**< The picture displayed on winning */
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


/**
 * Draw the cubes of a Rubik's cube
 * @param rubikCube The Rubik's cube to display
 */
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


/**
 * Draw the instructions
 * @param instructions A list of instructions to display
 * @param keyShortcut  An int representing the states of Shift and Ctrl
 */
void drawInstructions(instructionDisplay * instructions, int keyShortcut);


/**
 * Draw an instruction floating in front of a face
 * @param drawnInstruction The image structure for the instruction's image
 * @param ccw              Is the counterclockiwse modifier active ?
 * @param two              Is the double modifier active ?
 */
void drawInstruction(instructionDisplay drawnInstruction, int keyShortcut);


/**
 * Draw the XYZ or XYZi instruction
 * @param texStore The texture store to use
 * @param reversed True to show XYZi
 */
void drawXYZInstruction(textureStore texStore, bool reversed);


/**
 * Draw the skybox
 * @param textureId The ID of the skybox
 */
void drawSkybox(GLuint textureId);


/**
 * Draw the history
 * @param texStore  The texture store to use
 * @param moveStack A list of moves to display
 */
void drawHistory(textureStore texStore, mvstack moveStack);


/**
 * Draw the winning screen
 * @param texStore The texture store to use
 */
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
