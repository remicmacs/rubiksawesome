/**
 * @file view.c
 */

#include "view.h"
#include "graphics.h"
#include "math.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdbool.h>

void setWindow() {
  // Window configuration
  SDL_Init(SDL_INIT_VIDEO);
  atexit(SDL_Quit);

  // Set the window title
  SDL_WM_SetCaption("Rubiksawesome", NULL);
  // Set window size and colour depth
  SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, (double)640 / 480, 1, 1000);
  glEnable(GL_DEPTH_TEST);
}

rubikview generateView() {
  camera mainCamera = {
    (vector3) {0, 0, 0},
    (vector3) {5, 0, PI/2}
  };

  rubikview mainView;
  mainView.cubes = generateCubes();
  memcpy(&(mainView.mainCamera), &mainCamera, sizeof(camera));

  attachCubesToFaces(&mainView);

  return mainView;
}

cube * generateCubes() {
  cube * cubes = (cube *)malloc(27 * sizeof(cube));

  for (int cubeIndex = 0; cubeIndex < 27; cubeIndex++) {
    float x = (cubeIndex % 3) - 1;
    float y = ((cubeIndex % 9) / 3) - 1;
    float z = (cubeIndex / 9) - 1;

    /**
     * We use conditional compilation to enable/disable the center cube
     * Add -DCENTER_CUBE to your gcc compilation line to enable the center cube
     */
    #ifdef CENTER_CUBE
    if (cubeIndex == 13) {
      transform cubeTransform = {
        (vector3) {0, 0, 0},
        (vector3) {0, 0, 0},
        (vector3) {0, 0, 0},
        (vector3) {1.4, 1.4, 1.4}
      };
      colour gray = {20, 20, 20};
      cubes[13] = generateCube(cubeTransform);
      setCubeColour(gray, cubes + 13);
      printf("Generating the center cube");
    } else {
    #endif

    transform cubeTransform = {
      (vector3) {x, y, z},
      (vector3) {0, 0, 0},
      (vector3) {0, 0, 0},
      (vector3) {0.45, 0.45, 0.45}
    };
    cubes[cubeIndex] = generateCube(cubeTransform);

    #ifdef CENTER_CUBE
    }
    #endif
  }

  return cubes;
}

void attachCubesToFaces(rubikview * mainView) {
  // Mapping the bottom face
  for (int cubeIndex = 0; cubeIndex < 9; cubeIndex++) {
    mainView->bottomFace[cubeIndex] = &(mainView->cubes[cubeIndex]);
  }

  // Mapping the top face
  for (int cubeIndex = 18; cubeIndex < 27; cubeIndex++) {
    mainView->topFace[cubeIndex - 18] = &(mainView->cubes[cubeIndex]);
  }

  // Mapping the left face
  for (int cubeIndex = 0; cubeIndex < 27; cubeIndex += 3) {
    mainView->leftFace[cubeIndex / 3] = &(mainView->cubes[cubeIndex]);
  }

  // Mapping the right face
  for (int cubeIndex = 2; cubeIndex < 27; cubeIndex += 3) {
    mainView->rightFace[(cubeIndex - 2) / 3] = &(mainView->cubes[cubeIndex]);
  }

  // Mapping the front face
  for (int cubeIndex = 0; cubeIndex < 27; cubeIndex += 9) {
    for (int cubeSubIndex = 0; cubeSubIndex < 3; cubeSubIndex++) {
      mainView->frontFace[cubeSubIndex + (cubeIndex / 3)] = &(mainView->cubes[cubeIndex + cubeSubIndex]);
    }
  }

  // Mapping the back face
  for (int cubeIndex = 6; cubeIndex < 27; cubeIndex += 9) {
    for (int cubeSubIndex = 0; cubeSubIndex < 3; cubeSubIndex++) {
      mainView->backFace[cubeSubIndex + ((cubeIndex - 1) / 3) - 1] = &(mainView->cubes[cubeIndex + cubeSubIndex]);
    }
  }
}

void update(rubikview * mainView) {
  camera * mainCamera = &(mainView->mainCamera);
  cube * cubes = mainView->cubes;

  SDL_Event event;
  SDL_WaitEvent(&event);

  if (event.key.keysym.sym == SDLK_d && event.key.type == SDL_KEYDOWN) {
    rotateDown(mainView);
  }

  if (event.key.keysym.sym == SDLK_u && event.key.type == SDL_KEYDOWN) {
    rotateUp(mainView);
  }

  if (event.key.keysym.sym == SDLK_r && event.key.type == SDL_KEYDOWN) {
    rotateRight(mainView);
  }

  if (event.key.keysym.sym == SDLK_l && event.key.type == SDL_KEYDOWN) {
    rotateLeft(mainView);
  }

  if (event.key.keysym.sym == SDLK_f && event.key.type == SDL_KEYDOWN) {
    rotateFront(mainView);
  }

  if (event.key.keysym.sym == SDLK_b && event.key.type == SDL_KEYDOWN) {
    rotateBack(mainView);
  }

  if (event.key.keysym.sym == SDLK_DOWN && event.key.type == SDL_KEYDOWN) {
    if (mainCamera->angles.z > 0.000001) {
      mainCamera->angles.z -= PI / 36;
    }
  }
  else if (event.key.keysym.sym == SDLK_UP && event.key.type == SDL_KEYDOWN) {
    if (mainCamera->angles.z < PI - 0.000001) {
      mainCamera->angles.z += PI / 36;
    }
  }
  else if (event.key.keysym.sym == SDLK_RIGHT && event.key.type == SDL_KEYDOWN) {
    mainCamera->angles.y += PI / 36;
  }
  else if (event.key.keysym.sym == SDLK_LEFT && event.key.type == SDL_KEYDOWN) {
    mainCamera->angles.y -= PI / 36;
  }

  switch(event.type) {
    case SDL_QUIT:
      exit(0);
      break;
  }

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );

  mainCamera->position.x = mainCamera->angles.x * sinf(mainCamera->angles.z) * cosf(mainCamera->angles.y);
  mainCamera->position.y = mainCamera->angles.x * sinf(mainCamera->angles.z) * sinf(mainCamera->angles.y);
  mainCamera->position.z = mainCamera->angles.x * cosf(mainCamera->angles.z);

  gluLookAt(mainCamera->position.x, mainCamera->position.y, mainCamera->position.z, 0, 0, 0, 0, 0, 1);

  for (int cubeIndex = 0; cubeIndex < 27; cubeIndex++) {
    drawCube(cubes[cubeIndex], false);
  }

  // colour magenta = {255, 0, 255};
  // setCubeColour(magenta, mainView->frontFace[2]);

  glFlush();
  SDL_GL_SwapBuffers();
}

void rotateUp(rubikview * mainView) {
  for (int cubeIndex = 0; cubeIndex < 9; cubeIndex++) {
    for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
      rotateFaceZ(&(mainView->topFace[cubeIndex]->faces[faceIndex]), true);
    }
  }

  /**
   * F <- R <- B <- L
   *
   * Then we need to move each topest row from the contiguous faces to the
   * next face. In this case, we will put the Right on Front, the Back on
   * Right, the Left on Back and the Front on Left.
   *
   * For this, we'll use a list of the faces in order of their substition.
   * A temporary face is used as a swtich buffer.
   */

  // cube * tempFace[9];
  // cube ** faces[6] = {tempFace, mainView->frontFace, mainView->rightFace, mainView->backFace, mainView->leftFace, tempFace};
  // for (int faceIndex = 0; faceIndex < 5; faceIndex++) {
  //   faces[faceIndex][6] = faces[faceIndex + 1][6];
  //   faces[faceIndex][7] = faces[faceIndex + 1][7];
  //   faces[faceIndex][8] = faces[faceIndex + 1][8];
  // }

  cube * tempCubes[3];

  tempCubes[0] = mainView->frontFace[6];
  tempCubes[1] = mainView->frontFace[7];
  tempCubes[2] = mainView->frontFace[8];

  mainView->frontFace[6] = mainView->rightFace[6];
  mainView->frontFace[7] = mainView->rightFace[7];
  mainView->frontFace[8] = mainView->rightFace[8];

  mainView->rightFace[6] = mainView->backFace[8];
  mainView->rightFace[7] = mainView->backFace[7];
  mainView->rightFace[8] = mainView->backFace[6];

  mainView->backFace[8] = mainView->leftFace[8];
  mainView->backFace[7] = mainView->leftFace[7];
  mainView->backFace[6] = mainView->leftFace[6];

  mainView->leftFace[8] = tempCubes[0];
  mainView->leftFace[7] = tempCubes[1];
  mainView->leftFace[6] = tempCubes[2];


  // We also need to rotate the face we are rotating (here, the Top)
  cube * tempCube;

  // Rotate bottom corners
  tempCube = mainView->topFace[0];
  mainView->topFace[0] = mainView->topFace[2];
  mainView->topFace[2] = mainView->topFace[8];
  mainView->topFace[8] = mainView->topFace[6];
  mainView->topFace[6] = tempCube;

  // Rotate edges
  tempCube = mainView->topFace[1];
  mainView->topFace[1] = mainView->topFace[5];
  mainView->topFace[5] = mainView->topFace[7];
  mainView->topFace[7] = mainView->topFace[3];
  mainView->topFace[3] = tempCube;
}

void rotateDown(rubikview * mainView) {
  for (int cubeIndex = 0; cubeIndex < 9; cubeIndex++) {
    for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
      rotateFaceZ(&(mainView->bottomFace[cubeIndex]->faces[faceIndex]), false);
    }
  }

  /*cube * tempCubes[3];

  tempCubes[0] = mainView->frontFace[0];
  tempCubes[1] = mainView->frontFace[1];
  tempCubes[2] = mainView->frontFace[2];

  mainView->frontFace[0] = mainView->rightFace[0];
  mainView->frontFace[1] = mainView->rightFace[1];
  mainView->frontFace[2] = mainView->rightFace[2];

  mainView->rightFace[0] = mainView->backFace[0];
  mainView->rightFace[1] = mainView->backFace[1];
  mainView->rightFace[2] = mainView->backFace[2];

  mainView->backFace[0] = mainView->leftFace[0];
  mainView->backFace[1] = mainView->leftFace[1];
  mainView->backFace[2] = mainView->leftFace[2];

  mainView->leftFace[0] = tempCubes[0];
  mainView->leftFace[1] = tempCubes[1];
  mainView->leftFace[2] = tempCubes[2];*/
}

void rotateLeft(rubikview * mainView) {
  for (int cubeIndex = 0; cubeIndex < 9; cubeIndex++) {
    for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
      rotateFaceX(&(mainView->leftFace[cubeIndex]->faces[faceIndex]), false);
    }
  }
}

void rotateRight(rubikview * mainView) {
  for (int cubeIndex = 0; cubeIndex < 9; cubeIndex++) {
    for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
      rotateFaceX(&(mainView->rightFace[cubeIndex]->faces[faceIndex]), true);
    }
  }

  // Then we need to move each row on the left from the contiguous faces to the
  // next face.
  // F <- D <- B <- T
  cube * tempCubes[3];

  tempCubes[0] = mainView->frontFace[2];
  tempCubes[1] = mainView->frontFace[5];
  tempCubes[2] = mainView->frontFace[8];

  mainView->frontFace[2] = mainView->bottomFace[8];
  mainView->frontFace[5] = mainView->bottomFace[5];
  mainView->frontFace[8] = mainView->bottomFace[2];

  mainView->bottomFace[8] = mainView->backFace[8];
  mainView->bottomFace[5] = mainView->backFace[5];
  mainView->bottomFace[2] = mainView->backFace[2];

  mainView->backFace[8] = mainView->topFace[2];
  mainView->backFace[5] = mainView->topFace[5];
  mainView->backFace[2] = mainView->topFace[8];

  mainView->topFace[2] = tempCubes[0];
  mainView->topFace[5] = tempCubes[1];
  mainView->topFace[8] = tempCubes[2];

  // We also need to rotate the face we are rotating (here, the Top)
  cube * tempCube;

  // Rotate bottom corners
  tempCube = mainView->rightFace[0];
  mainView->rightFace[0] = mainView->rightFace[2];
  mainView->rightFace[2] = mainView->rightFace[8];
  mainView->rightFace[8] = mainView->rightFace[6];
  mainView->rightFace[6] = tempCube;

  // Rotate edges
  tempCube = mainView->rightFace[1];
  mainView->rightFace[1] = mainView->rightFace[5];
  mainView->rightFace[5] = mainView->rightFace[7];
  mainView->rightFace[7] = mainView->rightFace[3];
  mainView->rightFace[3] = tempCube;
}

void rotateFront(rubikview * mainView) {
  for (int cubeIndex = 0; cubeIndex < 9; cubeIndex++) {
    for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
      rotateFaceY(&(mainView->frontFace[cubeIndex]->faces[faceIndex]), false);
    }
  }

  /** L <- B <- R <- T */
  cube * tempCubes[3];

  tempCubes[0] = mainView->leftFace[6];
  tempCubes[1] = mainView->leftFace[3];
  tempCubes[2] = mainView->leftFace[0];

  mainView->leftFace[6] = mainView->bottomFace[0];
  mainView->leftFace[3] = mainView->bottomFace[1];
  mainView->leftFace[0] = mainView->bottomFace[2];

  mainView->bottomFace[0] = mainView->rightFace[0];
  mainView->bottomFace[1] = mainView->rightFace[3];
  mainView->bottomFace[2] = mainView->rightFace[6];

  mainView->rightFace[0] = mainView->topFace[2];
  mainView->rightFace[3] = mainView->topFace[1];
  mainView->rightFace[6] = mainView->topFace[0];

  mainView->topFace[2] = tempCubes[0];
  mainView->topFace[1] = tempCubes[1];
  mainView->topFace[0] = tempCubes[2];

  // We also need to rotate the face we are rotating (here, the Top)
  cube * tempCube;

  // Rotate bottom corners
  tempCube = mainView->frontFace[0];
  mainView->frontFace[0] = mainView->frontFace[2];
  mainView->frontFace[2] = mainView->frontFace[8];
  mainView->frontFace[8] = mainView->frontFace[6];
  mainView->frontFace[6] = tempCube;

  // Rotate edges
  tempCube = mainView->frontFace[1];
  mainView->frontFace[1] = mainView->frontFace[5];
  mainView->frontFace[5] = mainView->frontFace[7];
  mainView->frontFace[7] = mainView->frontFace[3];
  mainView->frontFace[3] = tempCube;
}

void rotateBack(rubikview * mainView) {
  for (int cubeIndex = 0; cubeIndex < 9; cubeIndex++) {
    mainView->backFace[cubeIndex]->cubeTransform.rotation.y -= PI / 2;
  }
}

void closeWindow() {
  SDL_Quit();
}
