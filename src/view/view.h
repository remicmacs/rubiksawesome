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


#define PI_DENOMINATOR 90
#define ROTATION_ANGLE (PI / PI_DENOMINATOR)
#define ANIMATIONS_STEP (PI_DENOMINATOR / 2)


/**
 * A structure holding the camera position and rotation
 */
typedef struct _camera {
  vector3 position;           /**< Position in the cartesian coordinates */
  vector3 angles;             /**< Position in the spherical coordinates */
  void (* rotate)(struct _camera * self, float zAngle, float yAngle);
  void (* zoom)(struct _camera * self, bool positive);
} camera;


/**
 * A structure holding every pointers to the sounds
 */
typedef struct _soundStore {
  Mix_Chunk * rumbling;   /**< Rumbling sound when the slices are moving */
  Mix_Chunk * clapping;   /**< Clapping sound for the end */
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
  SDL_Window * mainWindow;            /**< A pointer to the main window */
  SDL_Window * solveWindow;           /**< A pointer to the help window */
  bool windowToDisplay;               /**< Flag to indicate the need to display
                                      the help window */
  bool windowDisplayed;               /**< Flag to indicate that the help
                                      display has been displayed */
  TTF_Font * font;                    /**< A pointer to the font engine (may
                                      be removed) */
  void (* update)(struct _rubikview * mainView, mvqueue moveQueue, mvstack moveStack, mvqueue solveMoves);
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
 * Create and show the help window
 * @param mainView The pointer to the current view
 */
void showHelpWindow(rubikview * mainView);


/**
 * Redraw the view and handle events. This function must be called on every
 * frame.
 * @param mainView   The structure holding the view
 * @param moveQueue  A list of the moves that need to be animated
 * @param moveStack  A list of moves that has been done (history)
 * @param solveMoves A list of moves that can solve the cube (for the help)
 */
void update(rubikview * mainView, mvqueue moveQueue, mvstack moveStack, mvqueue solveMoves);


/**
 * Rotate the camera around the phi and theta angle
 * @param self   The camera itself
 * @param zAngle The theta angle
 * @param yAngle The phi angle
 */
void rotateCamera(camera * self, float zAngle, float yAngle);


/**
 * Zoom the camera (step by step)
 * @param self     The camera itself
 * @param positive True if you want to zoom out
 */
void zoomCamera(camera * self, bool positive);


vector3 polarToCartesian(vector3 polar);


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
 * Return a move depending on the pressed keys
 * @param  keysym      The pressed key
 * @param  keyShortcut An int representing the state of the Shift and Ctrl keys
 * @return             A move
 */
move getNextMove(SDL_Keycode keysym, int keyShortcut);


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
 * Play the winning sequence (set the winning flag to true and launch the
 * winning sound)
 * @param mainView Pointer to the view
 */
void playWinningSequence(rubikview * mainView);


/**
 * Close the window
 */
void closeWindow();

#endif
