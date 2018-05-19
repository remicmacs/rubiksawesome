/**
 * @file view.c
 */


#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdbool.h>
#include "animations.h"
#include "view.h"
#include "graphics.h"


void setWindow() {
  // Initialize everything
  SDL_Init(SDL_INIT_VIDEO);

  atexit(SDL_Quit);

  // Set the window title
  SDL_WM_SetCaption("Rubiksawesome", NULL);
  // Set window size and colour depth and initialize an OpenGL context
  SDL_SetVideoMode(800, 600, 32, SDL_OPENGL);

  // Set up of the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, (double)800 / 600, 1, 1000);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  SDL_version sdlVersion;
  SDL_VERSION(&sdlVersion);
  printf("SDL version: %d.%d.%d\n", sdlVersion.major, sdlVersion.minor, sdlVersion.patch);
  printf("OpenGL version: %s\n", glGetString(GL_VERSION));
  fflush(stdout);
}


rubikview generateView() {
  camera mainCamera = {
    (vector3) {0, 0, 0},
    (vector3) {5, - 3 * PI / 4, PI / 3}
  };

  rubikview mainView;
  memcpy(&(mainView.mainCamera), &mainCamera, sizeof(camera));
  mainView.rubikCube = generateRubikCube();
  mainView.animations = NULL;

  enum FaceType facesTypes[6] = {FRONT, RIGHT, TOP, DOWN, BACK, LEFT};

  for (int instructionIndex = 0; instructionIndex < 6; instructionIndex++) {
    mainView.instructions[instructionIndex] = generateInstructions(facesTypes[instructionIndex]);
  }

  mainView.update = &update;

  return mainView;
}


void update(rubikview * mainView) {
  camera * mainCamera = &(mainView->mainCamera);

  SDL_Event event;
  Uint8 *keystate = SDL_GetKeyState(NULL);

  while (SDL_PollEvent(&event)) {
    switch(event.type)
    {
      case SDL_MOUSEMOTION:
        if (event.type == SDL_MOUSEMOTION && event.motion.state == SDL_BUTTON_LMASK) {
          mainCamera->angles.y -= event.motion.xrel * 0.01;
          mainCamera->angles.z -= event.motion.yrel * 0.01;

          if (mainCamera->angles.z < 0) {
            mainCamera->angles.z = 0.000001;
          } else if (mainCamera->angles.z > PI) {
            mainCamera->angles.z = PI - 0.000001;
          }
        }
        break;
      case SDL_QUIT:
        exit(0);
        break;
    }

    if (event.button.button == SDL_BUTTON_WHEELUP) {
      mainCamera->angles.x -= 0.1;
    }

    if (event.button.button == SDL_BUTTON_WHEELDOWN) {
      mainCamera->angles.x += 0.1;
    }

    if (mainView->animations != NULL) {
      continue;
    }

    // DOWN ROTATION
    if (event.key.keysym.sym == SDLK_d && event.key.type == SDL_KEYDOWN) {
      animation * newAnimation = generateAnimation(ANIMATIONS_STEP, DOWN, 0, keystate[SDLK_LSHIFT]);
      addAnimation(&mainView->animations, newAnimation);
    }

    // UP ROTATION
    if (event.key.keysym.sym == SDLK_u && event.key.type == SDL_KEYDOWN) {
      animation * newAnimation = generateAnimation(ANIMATIONS_STEP, TOP, 2, !keystate[SDLK_LSHIFT]);
      addAnimation(&mainView->animations, newAnimation);
    }

    // RIGHT ROTATION
    if (event.key.keysym.sym == SDLK_r && event.key.type == SDL_KEYDOWN) {
      animation * newAnimation = generateAnimation(ANIMATIONS_STEP, RIGHT, 2, !keystate[SDLK_LSHIFT]);
      addAnimation(&mainView->animations, newAnimation);
    }

    // LEFT ROTATION
    if (event.key.keysym.sym == SDLK_l && event.key.type == SDL_KEYDOWN) {
      animation * newAnimation = generateAnimation(ANIMATIONS_STEP, LEFT, 0, keystate[SDLK_LSHIFT]);
      addAnimation(&mainView->animations, newAnimation);
    }

    // FRONT ROTATION
    if (event.key.keysym.sym == SDLK_f && event.key.type == SDL_KEYDOWN) {
      animation * newAnimation = generateAnimation(ANIMATIONS_STEP, FRONT, 0, keystate[SDLK_LSHIFT]);
      addAnimation(&mainView->animations, newAnimation);
    }

    // BACK ROTATION
    if (event.key.keysym.sym == SDLK_b && event.key.type == SDL_KEYDOWN) {
      animation * newAnimation = generateAnimation(ANIMATIONS_STEP, BACK, 2, !keystate[SDLK_LSHIFT]);
      addAnimation(&mainView->animations, newAnimation);
    }

    // MIDDLE ROTATION
    if (event.key.keysym.sym == SDLK_m && event.key.type == SDL_KEYDOWN) {
      animation * newAnimation = generateAnimation(ANIMATIONS_STEP, MIDDLE, 1, keystate[SDLK_LSHIFT]);
      addAnimation(&mainView->animations, newAnimation);
    }
  }

  animation * animationsPtr = mainView->animations;
  while (animationsPtr != NULL) {
    animationsPtr->update(animationsPtr, mainView->rubikCube);
    animationsPtr = animationsPtr->next;
    updateAnimationList(&mainView->animations);
  }

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );

  mainCamera->position.x = mainCamera->angles.x * sinf(mainCamera->angles.z) * cosf(mainCamera->angles.y);
  mainCamera->position.y = mainCamera->angles.x * sinf(mainCamera->angles.z) * sinf(mainCamera->angles.y);
  mainCamera->position.z = mainCamera->angles.x * cosf(mainCamera->angles.z);

  gluLookAt(mainCamera->position.x, mainCamera->position.y, mainCamera->position.z, 0, 0, 0, 0, 0, 1);

  GLfloat light_diffuse[] = {0.9, 0.9, 0.9, 1};  /* Red diffuse light. */
  GLfloat light_ambient[] = {0.1, 0.1, 0.1, 1};  /* Red diffuse light. */
  GLfloat light_specular[] = {0.6, 0.6, 0.6, 1};  /* Red diffuse light. */

  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  //glColorMaterial(GL_RIGHT, GL_SPECULAR);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  //glColorMaterial(GL_FRONT_RIGHT, GL_SPECULAR);
  glEnable(GL_COLOR_MATERIAL);

  for (int zIndex = 0; zIndex < 3; zIndex++) {
    for (int yIndex = 0; yIndex < 3; yIndex++) {
      for (int xIndex = 0; xIndex < 3; xIndex++) {
        drawCube(*mainView->rubikCube->cubes[xIndex][yIndex][zIndex], false);
      }
    }
  }

  for (int instructionIndex = 0; instructionIndex < 6; instructionIndex++) {
    drawInstruction(mainView->instructions[instructionIndex], keystate[SDLK_LSHIFT]);
  }

  glFlush();
  SDL_GL_SwapBuffers();
}

/*******************************************************************************
 * ROTATING FACES DATA
 *
 * Here we rotate the matrices 90° or -90°. The techniques as are follow:
 *
 * Rotating 90°:
 * 1. Transpose
 * 2. Reverse each row
 *
 * Rotating -90°:
 * 1. Transpose
 * 2. Reverse each column
 ******************************************************************************/


void rotateDataX(rubikcube * rubikCube, int xIndex, bool ccw) {
  /**
   * Transposing the matrix
   */
  for (int yIndex = 1; yIndex < 3; yIndex++) {
    for (int zIndex = 0; zIndex < yIndex; zIndex++) {
      cube3d * tempCube = rubikCube->cubes[xIndex][yIndex][zIndex];
      rubikCube->cubes[xIndex][yIndex][zIndex] = rubikCube->cubes[xIndex][zIndex][yIndex];
      rubikCube->cubes[xIndex][zIndex][yIndex] = tempCube;
    }
  }

  if (ccw) {
    /*
     * Exchanging the columns
     */
    for (int yIndex = 0; yIndex < 3; yIndex++) {
      cube3d * tempCube = rubikCube->cubes[xIndex][yIndex][0];
      rubikCube->cubes[xIndex][yIndex][0] = rubikCube->cubes[xIndex][yIndex][2];
      rubikCube->cubes[xIndex][yIndex][2] = tempCube;
    }
  } else {
    /*
     * Exchanging the rows
     */
    for (int zIndex = 0; zIndex < 3; zIndex++) {
      cube3d * tempCube = rubikCube->cubes[xIndex][0][zIndex];
      rubikCube->cubes[xIndex][0][zIndex] = rubikCube->cubes[xIndex][2][zIndex];
      rubikCube->cubes[xIndex][2][zIndex] = tempCube;
    }
  }
}


void rotateDataY(rubikcube * rubikCube, int yIndex, bool ccw) {
  /**
   * Transposing the matrix
   */
  for (int xIndex = 1; xIndex < 3; xIndex++) {
    for (int zIndex = 0; zIndex < xIndex; zIndex++) {
      cube3d * tempCube = rubikCube->cubes[xIndex][yIndex][zIndex];
      rubikCube->cubes[xIndex][yIndex][zIndex] = rubikCube->cubes[zIndex][yIndex][xIndex];
      rubikCube->cubes[zIndex][yIndex][xIndex] = tempCube;
    }
  }

  if (ccw) {
    /*
     * Exchanging the columns
     */
    for (int zIndex = 0; zIndex < 3; zIndex++) {
      cube3d * tempCube = rubikCube->cubes[0][yIndex][zIndex];
      rubikCube->cubes[0][yIndex][zIndex] = rubikCube->cubes[2][yIndex][zIndex];
      rubikCube->cubes[2][yIndex][zIndex] = tempCube;
    }
  } else {
    /*
     * Exchanging the rows
     */
    for (int xIndex = 0; xIndex < 3; xIndex++) {
      cube3d * tempCube = rubikCube->cubes[xIndex][yIndex][0];
      rubikCube->cubes[xIndex][yIndex][0] = rubikCube->cubes[xIndex][yIndex][2];
      rubikCube->cubes[xIndex][yIndex][2] = tempCube;
    }
  }
}


void rotateDataZ(rubikcube * rubikCube, int zIndex, bool ccw) {
  /**
   * Transposing the matrix
   */
  for (int xIndex = 1; xIndex < 3; xIndex++) {
    for (int yIndex = 0; yIndex < xIndex; yIndex++) {
      cube3d * tempCube = rubikCube->cubes[xIndex][yIndex][zIndex];
      rubikCube->cubes[xIndex][yIndex][zIndex] = rubikCube->cubes[yIndex][xIndex][zIndex];
      rubikCube->cubes[yIndex][xIndex][zIndex] = tempCube;
    }
  }

  if (!ccw) {
    /*
     * Exchanging the rows
     */
    for (int yIndex = 0; yIndex < 3; yIndex++) {
      cube3d * tempCube = rubikCube->cubes[0][yIndex][zIndex];
      rubikCube->cubes[0][yIndex][zIndex] = rubikCube->cubes[2][yIndex][zIndex];
      rubikCube->cubes[2][yIndex][zIndex] = tempCube;
    }
  } else {
    /*
     * Exchanging the columns
     */
    for (int xIndex = 0; xIndex < 3; xIndex++) {
      cube3d * tempCube = rubikCube->cubes[xIndex][0][zIndex];
      rubikCube->cubes[xIndex][0][zIndex] = rubikCube->cubes[xIndex][2][zIndex];
      rubikCube->cubes[xIndex][2][zIndex] = tempCube;
    }
  }
}


void closeWindow() {
  SDL_Quit();
}
