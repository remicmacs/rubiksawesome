/**
 * @file view.c
 */


#include <SDL/SDL.h>
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
  mainView.isMoving = false;
  mainView.rubikCube = generateRubikCube();
  mainView.animations = NULL;

  /**
   * We can enable animations with the -DANIMATIONS_ENABLED set
   */
  #ifdef ANIMATIONS_ENABLED
  mainView.animationsEnabled = true;
  #else
  mainView.animationsEnabled = false;
  #endif

  return mainView;
}


void update(rubikview * mainView) {
  camera * mainCamera = &(mainView->mainCamera);

  SDL_Event event;
  //Uint8 *keystate = SDL_GetKeyState(NULL);

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

    if (mainView->isMoving || mainView->animations != NULL) {
      continue;
    }

    // DOWN ROTATION
    if (event.key.keysym.sym == SDLK_d && event.key.type == SDL_KEYDOWN) {
      //rotateDown(mainView);
      animation * newAnimation = generateAnimation(ANIMATIONS_STEP, DOWN, 0, false);
      addAnimation(&mainView->animations, newAnimation);
    }

    // UP ROTATION
    if (event.key.keysym.sym == SDLK_u && event.key.type == SDL_KEYDOWN) {
      //rotateUp(mainView);
      animation * newAnimation = generateAnimation(ANIMATIONS_STEP, TOP, 2, true);
      addAnimation(&mainView->animations, newAnimation);
    }

    if (event.key.keysym.sym == SDLK_r && event.key.type == SDL_KEYDOWN) {
      //rotateRight(mainView);
      animation * newAnimation = generateAnimation(ANIMATIONS_STEP, RIGHT, 2, true);
      addAnimation(&mainView->animations, newAnimation);
    }

    if (event.key.keysym.sym == SDLK_l && event.key.type == SDL_KEYDOWN) {
      //rotateLeft(mainView);
      animation * newAnimation = generateAnimation(ANIMATIONS_STEP, LEFT, 0, false);
      addAnimation(&mainView->animations, newAnimation);
    }

    if (event.key.keysym.sym == SDLK_f && event.key.type == SDL_KEYDOWN) {
      //rotateFront(mainView);
      animation * newAnimation = generateAnimation(ANIMATIONS_STEP, FRONT, 0, false);
      addAnimation(&mainView->animations, newAnimation);
    }

    if (event.key.keysym.sym == SDLK_b && event.key.type == SDL_KEYDOWN) {
      //rotateBack(mainView);
      animation * newAnimation = generateAnimation(ANIMATIONS_STEP, BACK, 2, true);
      addAnimation(&mainView->animations, newAnimation);
    }

    if (event.key.keysym.sym == SDLK_m && event.key.type == SDL_KEYDOWN) {
      //rotateMiddle(mainView);
      animation * newAnimation = generateAnimation(ANIMATIONS_STEP, MIDDLE, 1, false);
      addAnimation(&mainView->animations, newAnimation);
    }
  }

  if (mainView->isMoving) {
    switch(mainView->cubeAnimation.animatedFace) {
      case TOP:
        animateUp(mainView);
        break;
      case DOWN:
        animateDown(mainView);
        break;
      case LEFT:
        animateLeft(mainView);
        break;
      case RIGHT:
        animateRight(mainView);
        break;
      case FRONT:
        animateFront(mainView);
        break;
      case BACK:
        animateBack(mainView);
        break;
      case MIDDLE:
        animateMiddle(mainView);
        break;
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

  for (int zIndex = 0; zIndex < 3; zIndex++) {
    for (int yIndex = 0; yIndex < 3; yIndex++) {
      for (int xIndex = 0; xIndex < 3; xIndex++) {
        drawCube(*mainView->rubikCube->cubes[xIndex][yIndex][zIndex], false);
      }
    }
  }

  glFlush();
  SDL_GL_SwapBuffers();
}


void rotateUp(rubikview * mainView) {
  mainView->cubeAnimation.currentStep = 0;
  mainView->cubeAnimation.targetStep = ANIMATIONS_STEP;
  mainView->cubeAnimation.isActive = true;
  mainView->isMoving = true;
  mainView->cubeAnimation.animatedFace = TOP;
}


void rotateDown(rubikview * mainView) {
  mainView->cubeAnimation.currentStep = 0;
  mainView->cubeAnimation.targetStep = ANIMATIONS_STEP;
  mainView->cubeAnimation.isActive = true;
  mainView->isMoving = true;
  mainView->cubeAnimation.animatedFace = DOWN;
}


void rotateLeft(rubikview * mainView) {
  mainView->cubeAnimation.currentStep = 0;
  mainView->cubeAnimation.targetStep = ANIMATIONS_STEP;
  mainView->cubeAnimation.isActive = true;
  mainView->isMoving = true;
  mainView->cubeAnimation.animatedFace = LEFT;
}


void rotateRight(rubikview * mainView) {
  mainView->cubeAnimation.currentStep = 0;
  mainView->cubeAnimation.targetStep = ANIMATIONS_STEP;
  mainView->cubeAnimation.isActive = true;
  mainView->isMoving = true;
  mainView->cubeAnimation.animatedFace = RIGHT;
}


void rotateMiddle(rubikview * mainView) {
  mainView->cubeAnimation.currentStep = 0;
  mainView->cubeAnimation.targetStep = ANIMATIONS_STEP;
  mainView->cubeAnimation.isActive = true;
  mainView->isMoving = true;
  mainView->cubeAnimation.animatedFace = MIDDLE;
}


void rotateFront(rubikview * mainView) {
  mainView->cubeAnimation.currentStep = 0;
  mainView->cubeAnimation.targetStep = ANIMATIONS_STEP;
  mainView->cubeAnimation.isActive = true;
  mainView->isMoving = true;
  mainView->cubeAnimation.animatedFace = FRONT;
}


void rotateBack(rubikview * mainView) {
  mainView->cubeAnimation.currentStep = 0;
  mainView->cubeAnimation.targetStep = ANIMATIONS_STEP;
  mainView->cubeAnimation.isActive = true;
  mainView->isMoving = true;
  mainView->cubeAnimation.animatedFace = BACK;
}


/*******************************************************************************
 * ANIMATIONS
 * Define animations functions. They are called everytime we need to update the
 * animations
 ******************************************************************************/


void animateUp(rubikview * mainView) {
  int currentStep = mainView->cubeAnimation.currentStep;
  int targetStep = mainView->cubeAnimation.targetStep;

  if (currentStep == targetStep) {
    mainView->cubeAnimation.currentStep = 0;
    mainView->cubeAnimation.isActive = false;
    mainView->isMoving = false;
    rotateDataZ(mainView->rubikCube, 2, true);
  } else {
    for (int xIndex = 0; xIndex < 3; xIndex++) {
      for (int yIndex = 0; yIndex < 3; yIndex++) {
        for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
          rotateFaceZ(&mainView->rubikCube->cubes[xIndex][yIndex][2]->faces[faceIndex], ROTATION_ANGLE, true);
        }
      }
    }
    mainView->cubeAnimation.currentStep++;
  }
}


void animateDown(rubikview * mainView) {
  int currentStep = mainView->cubeAnimation.currentStep;
  int targetStep = mainView->cubeAnimation.targetStep;

  if (currentStep == targetStep) {
    mainView->cubeAnimation.currentStep = 0;
    mainView->cubeAnimation.isActive = false;
    mainView->isMoving = false;
    rotateDataZ(mainView->rubikCube, 0, false);
  } else {
    for (int xIndex = 0; xIndex < 3; xIndex++) {
      for (int yIndex = 0; yIndex < 3; yIndex++) {
        for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
          rotateFaceZ(&mainView->rubikCube->cubes[xIndex][yIndex][0]->faces[faceIndex], ROTATION_ANGLE, false);
        }
      }
    }
    mainView->cubeAnimation.currentStep++;
  }
}


void animateLeft(rubikview * mainView) {
  int currentStep = mainView->cubeAnimation.currentStep;
  int targetStep = mainView->cubeAnimation.targetStep;

  if (currentStep == targetStep) {
    mainView->cubeAnimation.currentStep = 0;
    mainView->cubeAnimation.isActive = false;
    mainView->isMoving = false;
    rotateDataX(mainView->rubikCube, 0, false);
  } else {
    for (int xIndex = 0; xIndex < 3; xIndex++) {
      for (int yIndex = 0; yIndex < 3; yIndex++) {
        for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
          rotateFaceX(&mainView->rubikCube->cubes[0][xIndex][yIndex]->faces[faceIndex], ROTATION_ANGLE, false);
        }
      }
    }
    mainView->cubeAnimation.currentStep++;
  }
}


void animateRight(rubikview * mainView) {
  int currentStep = mainView->cubeAnimation.currentStep;
  int targetStep = mainView->cubeAnimation.targetStep;

  if (currentStep == targetStep) {
    mainView->cubeAnimation.currentStep = 0;
    mainView->cubeAnimation.isActive = false;
    mainView->isMoving = false;
    rotateDataX(mainView->rubikCube, 2, true);
  } else {
    for (int xIndex = 0; xIndex < 3; xIndex++) {
      for (int yIndex = 0; yIndex < 3; yIndex++) {
        for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
          rotateFaceX(&mainView->rubikCube->cubes[2][xIndex][yIndex]->faces[faceIndex], ROTATION_ANGLE, true);
        }
      }
    }
    mainView->cubeAnimation.currentStep++;
  }
}


void animateMiddle(rubikview * mainView) {
  int currentStep = mainView->cubeAnimation.currentStep;
  int targetStep = mainView->cubeAnimation.targetStep;

  if (currentStep == targetStep) {
    mainView->cubeAnimation.currentStep = 0;
    mainView->cubeAnimation.isActive = false;
    mainView->isMoving = false;
    rotateDataX(mainView->rubikCube, 1, false);
  } else {
    for (int xIndex = 0; xIndex < 3; xIndex++) {
      for (int yIndex = 0; yIndex < 3; yIndex++) {
        for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
          rotateFaceX(&mainView->rubikCube->cubes[1][xIndex][yIndex]->faces[faceIndex], ROTATION_ANGLE, false);
        }
      }
    }
    mainView->cubeAnimation.currentStep++;
  }
}


void animateFront(rubikview * mainView) {
  int currentStep = mainView->cubeAnimation.currentStep;
  int targetStep = mainView->cubeAnimation.targetStep;

  if (currentStep == targetStep) {
    mainView->cubeAnimation.currentStep = 0;
    mainView->cubeAnimation.isActive = false;
    mainView->isMoving = false;
    rotateDataY(mainView->rubikCube, 0, false);
  } else {
    for (int xIndex = 0; xIndex < 3; xIndex++) {
      for (int yIndex = 0; yIndex < 3; yIndex++) {
        for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
          rotateFaceY(&mainView->rubikCube->cubes[xIndex][0][yIndex]->faces[faceIndex], ROTATION_ANGLE, false);
        }
      }
    }
    mainView->cubeAnimation.currentStep++;
  }
}


void animateBack(rubikview * mainView) {
  int currentStep = mainView->cubeAnimation.currentStep;
  int targetStep = mainView->cubeAnimation.targetStep;

  if (currentStep == targetStep) {
    mainView->cubeAnimation.currentStep = 0;
    mainView->cubeAnimation.isActive = false;
    mainView->isMoving = false;
    rotateDataY(mainView->rubikCube, 2, true);
  } else {
    for (int xIndex = 0; xIndex < 3; xIndex++) {
      for (int yIndex = 0; yIndex < 3; yIndex++) {
        for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
          rotateFaceY(&mainView->rubikCube->cubes[xIndex][2][yIndex]->faces[faceIndex], ROTATION_ANGLE, true);
        }
      }
    }
    mainView->cubeAnimation.currentStep++;
  }
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
      cube * tempCube = rubikCube->cubes[xIndex][yIndex][zIndex];
      rubikCube->cubes[xIndex][yIndex][zIndex] = rubikCube->cubes[xIndex][zIndex][yIndex];
      rubikCube->cubes[xIndex][zIndex][yIndex] = tempCube;
    }
  }

  if (ccw) {
    /*
     * Exchanging the columns
     */
    for (int yIndex = 0; yIndex < 3; yIndex++) {
      cube * tempCube = rubikCube->cubes[xIndex][yIndex][0];
      rubikCube->cubes[xIndex][yIndex][0] = rubikCube->cubes[xIndex][yIndex][2];
      rubikCube->cubes[xIndex][yIndex][2] = tempCube;
    }
  } else {
    /*
     * Exchanging the rows
     */
    for (int zIndex = 0; zIndex < 3; zIndex++) {
      cube * tempCube = rubikCube->cubes[xIndex][0][zIndex];
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
      cube * tempCube = rubikCube->cubes[xIndex][yIndex][zIndex];
      rubikCube->cubes[xIndex][yIndex][zIndex] = rubikCube->cubes[zIndex][yIndex][xIndex];
      rubikCube->cubes[zIndex][yIndex][xIndex] = tempCube;
    }
  }

  if (ccw) {
    /*
     * Exchanging the columns
     */
    for (int zIndex = 0; zIndex < 3; zIndex++) {
      cube * tempCube = rubikCube->cubes[0][yIndex][zIndex];
      rubikCube->cubes[0][yIndex][zIndex] = rubikCube->cubes[2][yIndex][zIndex];
      rubikCube->cubes[2][yIndex][zIndex] = tempCube;
    }
  } else {
    /*
     * Exchanging the rows
     */
    for (int xIndex = 0; xIndex < 3; xIndex++) {
      cube * tempCube = rubikCube->cubes[xIndex][yIndex][0];
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
      cube * tempCube = rubikCube->cubes[xIndex][yIndex][zIndex];
      rubikCube->cubes[xIndex][yIndex][zIndex] = rubikCube->cubes[yIndex][xIndex][zIndex];
      rubikCube->cubes[yIndex][xIndex][zIndex] = tempCube;
    }
  }

  if (!ccw) {
    /*
     * Exchanging the rows
     */
    for (int yIndex = 0; yIndex < 3; yIndex++) {
      cube * tempCube = rubikCube->cubes[0][yIndex][zIndex];
      rubikCube->cubes[0][yIndex][zIndex] = rubikCube->cubes[2][yIndex][zIndex];
      rubikCube->cubes[2][yIndex][zIndex] = tempCube;
    }
  } else {
    /*
     * Exchanging the columns
     */
    for (int xIndex = 0; xIndex < 3; xIndex++) {
      cube * tempCube = rubikCube->cubes[xIndex][0][zIndex];
      rubikCube->cubes[xIndex][0][zIndex] = rubikCube->cubes[xIndex][2][zIndex];
      rubikCube->cubes[xIndex][2][zIndex] = tempCube;
    }
  }
}


void closeWindow() {
  SDL_Quit();
}
