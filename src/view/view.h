/**
 * @file view.h
 * Defines functions to display and manipulate the Rubik's cube
 */


#ifndef VIEW_H
#define VIEW_H


#include <math.h>
#include <stdbool.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "graphics.h"
#include "animations.h"
#include "../model/cube.h"
#include "../controller/commandQueue.h"


#define PI_DENOMINATOR 1080
#define ROTATION_ANGLE (PI / PI_DENOMINATOR)
#define ANIMATIONS_STEP (PI_DENOMINATOR / 2)


/**
 * A structure holding the camera position and rotation
 */
typedef struct _camera {
  vector3 position;           /**< Position in the cartesian coordinates */
  vector3 angles;             /**< Position in the spherical coordinates */
} camera;


typedef struct _soundStore {
  Mix_Chunk * rumbling;
  Mix_Chunk * clapping;
} soundStore;


/**
 * A structure holding all the informations related to the view
 */
typedef struct _rubikview {
  camera mainCamera;                  /**< The camera in the view */
  rubikcube * rubikCube;              /**< The Rubik's cube */
  animationStack * animStack;         /**< Animation stack to update them
                                      serially */
  instructionDisplay instructions[6]; /**< An array of images for the
                                      instructions */
  textureStore texStore;              /**< Store for the textures */
  soundStore sndStore;                /**< Store for the sounds */
  bool instructionsDisplayed;         /**< True to show the instructions */
  bool gameWon;                       /**< True if the game is finished */
  int konamiCount;                    /**< State of the konami code */
  SDL_Window * mainWindow;
  SDL_Window * solveWindow;
  bool windowToDisplay;
  bool windowDisplayed;
  TTF_Font * font;
  void (* update)(struct _rubikview * mainView, mvqueue moveQueue, mvstack moveStack, move * solveMoves);
  void (* animate)(struct _rubikview * self, move order, bool fast);
} rubikview;


/**
 * Set SDL
 */
void setSDL();


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
void update(rubikview * mainView, mvqueue moveQueue, mvstack moveStack, move * solveMoves);


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
 * Generate a sound store
 * @return The sound store that has been generated
 */
soundStore generateSoundStore();


/**
 * Reset the view passed as parameter
 *
 * Helper function to reset the view to a new game position.
 *
 * @param aView - Pointer to the rubikview to reset. Unallocates the memory of
 * each nested structure
 */
void resetView(rubikview * aView);


/**
 * Close the window
 *
 * @param mainView - Pointer to the view
 */
void closeWindow(rubikview * mainView);

#endif
