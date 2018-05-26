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
#include "../model/cube.h"
#include "../controller/commandQueue.h"


void setWindow() {
  /*
   * Initialize SDL
   */
  SDL_Init(SDL_INIT_VIDEO);

  /*
   * Bind the SDL_Quit() function to the program's exit
   */
  atexit(SDL_Quit);

  /*
   * Enabling SDL multisampling (antialiasing)
   */
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

  /*
   *  Set the window title and set the window size, the colour depth and
   *  context to OpenGL
   */
  SDL_WM_SetCaption("Rubiksawesome", NULL);
  SDL_SetVideoMode(800, 600, 32, SDL_OPENGL);

  /*
   * Set up of the projection matrix to use perspective
   */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, (double)800 / 600, 1, 1000);

  /*
   * Enable depth testing (allows objects to hide each others)
   */
  glEnable(GL_DEPTH_TEST);

  /*
   * Enable transparency by enabling blending between alpha channel and
   * previous alpha channel
   */
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  /*
   * Enable lighting
   */
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  /*
   * Enable OpenGL multisampling (antialiasing)
   */
  glEnable(GL_MULTISAMPLE);

  // Create light components
  GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
  GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
  GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
  GLfloat position[] = { -1.0f, 0, 0, 1.0f };

  // Assign created components to GL_LIGHT0
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
  glLightfv(GL_LIGHT0, GL_POSITION, position);

  /*
   * Display SDL and OpenGL versions
   */
  SDL_version sdlVersion;
  SDL_VERSION(&sdlVersion);
  printf("SDL version: %d.%d.%d\n", sdlVersion.major, sdlVersion.minor, sdlVersion.patch);
  printf("OpenGL version: %s\n", glGetString(GL_VERSION));
  fflush(stdout);
}


rubikview generateView() {
  /*
   * Set the camera starting position
   */
  camera mainCamera = {
    (vector3) {0, 0, 0},
    (vector3) {8, - 3 * PI / 4, PI / 3}
  };

  /*
   * Create the cube and assign the camera, the rubik's cube and an empty
   * animations list
   */
  rubikview mainView;
  memcpy(&(mainView.mainCamera), &mainCamera, sizeof(camera));
  mainView.rubikCube = generateRubikCube();
  mainView.animations = NULL;

  /*
   * Generates instructions and add them to the view (hidden by default)
   */
  enum FaceType facesTypes[6] = {FRONT, RIGHT, TOP, DOWN, BACK, LEFT};
  for (int instructionIndex = 0; instructionIndex < 6; instructionIndex++) {
    mainView.instructions[instructionIndex] = generateInstructions(facesTypes[instructionIndex]);
  }
  mainView.instructionsDisplayed = false;

  generateCubemapTexture(&mainView.skybox);

  /*
   * Bind the update() function to the update structure member
   */
  mainView.update = &update;

  mainView.animate = &parseOrder;

  return mainView;
}


void update(rubikview * mainView, movequeue * moveQueue) {
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
      if (mainCamera->angles.x < 4) {
        mainCamera->angles.x = 4;
      }
    }

    if (event.button.button == SDL_BUTTON_WHEELDOWN) {
      mainCamera->angles.x += 0.1;
      if (mainCamera->angles.x > 50) {
        mainCamera->angles.x = 50;
      }
    }

    if (event.key.keysym.sym == SDLK_i && event.key.type == SDL_KEYDOWN) {
      mainView->instructionsDisplayed = !mainView->instructionsDisplayed;
    }

    if (mainView->animations != NULL) {
      continue;
    }

    move newMove;

    // DOWN ROTATION
    if (event.key.keysym.sym == SDLK_d && event.key.type == SDL_KEYDOWN) {
      if (keystate[SDLK_LSHIFT] && keystate[SDLK_LCTRL]) {
        newMove = di;
      } else if (keystate[SDLK_LSHIFT] && !keystate[SDLK_LCTRL]) {
        newMove = Di;
      } else if (!keystate[SDLK_LSHIFT] && keystate[SDLK_LCTRL]) {
        newMove = d;
      } else {
        newMove = D;
      }

      enqueue(moveQueue, newMove);
    }

    // UP ROTATION
    if (event.key.keysym.sym == SDLK_u && event.key.type == SDL_KEYDOWN) {
      if (keystate[SDLK_LSHIFT] && keystate[SDLK_LCTRL]) {
        newMove = ui;
      } else if (keystate[SDLK_LSHIFT] && !keystate[SDLK_LCTRL]) {
        newMove = Ui;
      } else if (!keystate[SDLK_LSHIFT] && keystate[SDLK_LCTRL]) {
        newMove = u;
      } else {
        newMove = U;
      }

      enqueue(moveQueue, newMove);
    }

    // RIGHT ROTATION
    if (event.key.keysym.sym == SDLK_r && event.key.type == SDL_KEYDOWN) {
      if (keystate[SDLK_LSHIFT] && keystate[SDLK_LCTRL]) {
        newMove = ri;
      } else if (keystate[SDLK_LSHIFT] && !keystate[SDLK_LCTRL]) {
        newMove = Ri;
      } else if (!keystate[SDLK_LSHIFT] && keystate[SDLK_LCTRL]) {
        newMove = r;
      } else {
        newMove = R;
      }

      enqueue(moveQueue, newMove);
    }

    // LEFT ROTATION
    if (event.key.keysym.sym == SDLK_l && event.key.type == SDL_KEYDOWN) {
      if (keystate[SDLK_LSHIFT] && keystate[SDLK_LCTRL]) {
        newMove = li;
      } else if (keystate[SDLK_LSHIFT] && !keystate[SDLK_LCTRL]) {
        newMove = Li;
      } else if (!keystate[SDLK_LSHIFT] && keystate[SDLK_LCTRL]) {
        newMove = l;
      } else {
        newMove = L;
      }

      enqueue(moveQueue, newMove);
    }

    // FRONT ROTATION
    if (event.key.keysym.sym == SDLK_f && event.key.type == SDL_KEYDOWN) {
      if (keystate[SDLK_LSHIFT] && keystate[SDLK_LCTRL]) {
        newMove = fi;
      } else if (keystate[SDLK_LSHIFT] && !keystate[SDLK_LCTRL]) {
        newMove = Fi;
      } else if (!keystate[SDLK_LSHIFT] && keystate[SDLK_LCTRL]) {
        newMove = f;
      } else {
        newMove = F;
      }

      enqueue(moveQueue, newMove);
    }

    // BACK ROTATION
    if (event.key.keysym.sym == SDLK_b && event.key.type == SDL_KEYDOWN) {
      if (keystate[SDLK_LSHIFT] && keystate[SDLK_LCTRL]) {
        newMove = bi;
      } else if (keystate[SDLK_LSHIFT] && !keystate[SDLK_LCTRL]) {
        newMove = Bi;
      } else if (!keystate[SDLK_LSHIFT] && keystate[SDLK_LCTRL]) {
        newMove = b;
      } else {
        newMove = B;
      }

      enqueue(moveQueue, newMove);
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

  drawSkybox(mainView->skybox);

  GLfloat light_diffuse[] = {1, 1, 1, 1};
  GLfloat light_specular[] = {0.9, 0.9, 0.9, 1};

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, light_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, light_specular);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glMateriali(GL_FRONT, GL_SHININESS, 96);
  glEnable(GL_COLOR_MATERIAL);

  for (int zIndex = 0; zIndex < 3; zIndex++) {
    for (int yIndex = 0; yIndex < 3; yIndex++) {
      for (int xIndex = 0; xIndex < 3; xIndex++) {
        drawCube(*mainView->rubikCube->cubes[xIndex][yIndex][zIndex], false);
      }
    }
  }

  if (mainView->instructionsDisplayed) {
    for (int instructionIndex = 0; instructionIndex < 6; instructionIndex++) {
      drawInstruction(mainView->instructions[instructionIndex], keystate[SDLK_LSHIFT], keystate[SDLK_LCTRL]);
    }
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


void parseOrder(rubikview * mainView, move order, bool fast) {
  animation * newAnimation;
  float rotationAngle = fast ? PI / 2 : ROTATION_ANGLE;
  switch (order) {
    case U:
      newAnimation = generateAnimation(TOP, 2, rotationAngle, true);
      addAnimation(&mainView->animations, newAnimation);
      break;
    case D:
      newAnimation = generateAnimation(DOWN, 0, rotationAngle, false);
      addAnimation(&mainView->animations, newAnimation);
      break;
    case R:
      newAnimation = generateAnimation(RIGHT, 2, rotationAngle, true);
      addAnimation(&mainView->animations, newAnimation);
      break;
    case L:
      newAnimation = generateAnimation(LEFT, 0, rotationAngle, false);
      addAnimation(&mainView->animations, newAnimation);
      break;
    case F:
      newAnimation = generateAnimation(FRONT, 0, rotationAngle, false);
      addAnimation(&mainView->animations, newAnimation);
      break;
    case B:
      newAnimation = generateAnimation(BACK, 2, rotationAngle, true);
      addAnimation(&mainView->animations, newAnimation);
      break;

    case Ui:
      newAnimation = generateAnimation(TOP, 2, rotationAngle, false);
      addAnimation(&mainView->animations, newAnimation);
      break;
    case Di:
      newAnimation = generateAnimation(DOWN, 0, rotationAngle, true);
      addAnimation(&mainView->animations, newAnimation);
      break;
    case Ri:
      newAnimation = generateAnimation(RIGHT, 2, rotationAngle, false);
      addAnimation(&mainView->animations, newAnimation);
      break;
    case Li:
      newAnimation = generateAnimation(LEFT, 0, rotationAngle, true);
      addAnimation(&mainView->animations, newAnimation);
      break;
    case Fi:
      newAnimation = generateAnimation(FRONT, 0, rotationAngle, true);
      addAnimation(&mainView->animations, newAnimation);
      break;
    case Bi:
      newAnimation = generateAnimation(BACK, 2, rotationAngle, false);
      addAnimation(&mainView->animations, newAnimation);
      break;

    case u:
      newAnimation = generateAnimation(TOP, 2, rotationAngle, true);
      addAnimation(&mainView->animations, newAnimation);
      newAnimation = generateAnimation(TOP, 1, rotationAngle, true);
      addAnimation(&mainView->animations, newAnimation);
      break;
    case d:
      newAnimation = generateAnimation(DOWN, 0, rotationAngle, false);
      addAnimation(&mainView->animations, newAnimation);
      newAnimation = generateAnimation(DOWN, 1, rotationAngle, false);
      addAnimation(&mainView->animations, newAnimation);
      break;
    case r:
      newAnimation = generateAnimation(RIGHT, 2, rotationAngle, true);
      addAnimation(&mainView->animations, newAnimation);
      newAnimation = generateAnimation(RIGHT, 1, rotationAngle, true);
      addAnimation(&mainView->animations, newAnimation);
      break;
    case l:
      newAnimation = generateAnimation(LEFT, 0, rotationAngle, false);
      addAnimation(&mainView->animations, newAnimation);
      newAnimation = generateAnimation(LEFT, 1, rotationAngle, false);
      addAnimation(&mainView->animations, newAnimation);
      break;
    case f:
      newAnimation = generateAnimation(FRONT, 0, rotationAngle, false);
      addAnimation(&mainView->animations, newAnimation);
      newAnimation = generateAnimation(FRONT, 1, rotationAngle, false);
      addAnimation(&mainView->animations, newAnimation);
      break;
    case b:
      newAnimation = generateAnimation(BACK, 2, rotationAngle, true);
      addAnimation(&mainView->animations, newAnimation);
      newAnimation = generateAnimation(BACK, 1, rotationAngle, true);
      addAnimation(&mainView->animations, newAnimation);
      break;

    case ui:
      newAnimation = generateAnimation(TOP, 2, rotationAngle, false);
      addAnimation(&mainView->animations, newAnimation);
      newAnimation = generateAnimation(TOP, 1, rotationAngle, false);
      addAnimation(&mainView->animations, newAnimation);
      break;
    case di:
      newAnimation = generateAnimation(DOWN, 0, rotationAngle, true);
      addAnimation(&mainView->animations, newAnimation);
      newAnimation = generateAnimation(DOWN, 1, rotationAngle, true);
      addAnimation(&mainView->animations, newAnimation);
      break;
    case ri:
      newAnimation = generateAnimation(RIGHT, 2, rotationAngle, false);
      addAnimation(&mainView->animations, newAnimation);
      newAnimation = generateAnimation(RIGHT, 1, rotationAngle, false);
      addAnimation(&mainView->animations, newAnimation);
      break;
    case li:
      newAnimation = generateAnimation(LEFT, 0, rotationAngle, true);
      addAnimation(&mainView->animations, newAnimation);
      newAnimation = generateAnimation(LEFT, 1, rotationAngle, true);
      addAnimation(&mainView->animations, newAnimation);
      break;
    case fi:
      newAnimation = generateAnimation(FRONT, 0, rotationAngle, true);
      addAnimation(&mainView->animations, newAnimation);
      newAnimation = generateAnimation(FRONT, 1, rotationAngle, true);
      addAnimation(&mainView->animations, newAnimation);
      break;
    case bi:
      newAnimation = generateAnimation(BACK, 2, rotationAngle, false);
      addAnimation(&mainView->animations, newAnimation);
      newAnimation = generateAnimation(BACK, 1, rotationAngle, false);
      addAnimation(&mainView->animations, newAnimation);
      break;

    default:
      break;
  }
}


void closeWindow() {
  SDL_Quit();
}
