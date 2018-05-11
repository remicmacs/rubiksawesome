#include "view.h"
#include "graphics.h"
#include "math.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void setWindow() {
  // Window configuration
  SDL_Init(SDL_INIT_VIDEO);
  atexit(SDL_Quit);
  SDL_WM_SetCaption("Rubiksawesome", NULL);
  SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);

  glMatrixMode( GL_PROJECTION );
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

  return mainView;
}

cube * generateCubes() {
  cube * cubes = (cube *)malloc(27 * sizeof(cube));

  for (int cubeIndex = 0; cubeIndex < 27; cubeIndex++) {
    vector3 position = {
      (float)((cubeIndex % 3) - 1),
      (float)(((cubeIndex % 9) / 3) - 1),
      (float)((cubeIndex / 9) - 1)
    };

    transform cubeTransform = {
      position,
      (vector3) {0, 0, 0},
      (vector3) {0.45, 0.45, 0.45}
    };
    cubes[cubeIndex] = generateCube(cubeTransform);
  }

  /*transform cubeTransform = {
    (vector3) {0, 0, 0},
    (vector3) {0, 0, 0},
    (vector3) {1.4, 1.4, 1.4}
  };
  colour gray = {20, 20, 20};
  //cubes[13] = generateCube(cubeTransform);
  //setCubeColour(gray, cubes + 13);*/

  return cubes;
}

void update(camera * mainCamera, cube * cubes) {
  SDL_Event event;

  SDL_WaitEvent(&event);

  if (event.key.keysym.sym == SDLK_d && event.key.type == SDL_KEYDOWN) {
    for (int cubeIndex = 0; cubeIndex < 9; cubeIndex++) {
      cubes[cubeIndex].cubeTransform.rotation.z += PI / 4;
    }
  }

  if (event.key.keysym.sym == SDLK_u && event.key.type == SDL_KEYDOWN) {
    for (int cubeIndex = 18; cubeIndex < 27; cubeIndex++) {
      cubes[cubeIndex].cubeTransform.rotation.z += PI / 4;
    }
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
    drawCube(cubes[cubeIndex]);
  }

  glFlush();
  SDL_GL_SwapBuffers();
}

void closeWindow() {
  SDL_Quit();
}
