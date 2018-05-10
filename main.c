#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "graphics.h"

#define ONE_DEGREE 0.00707355302
#define PI 3.141592653589793

enum faceType {
  TOP,
  BOTTOM,
  FRONT,
  BACK,
  RIGHT,
  LEFT
};

void drawCube2();

int main(int argc, char **argv) {
  cube cubes[27];

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

  transform cubeTransform = {
    (vector3) {0, 0, 0},
    (vector3) {0, 0, 0},
    (vector3) {1.4, 1.4, 1.4}
  };
  colour gray = {20, 20, 20};
  cubes[13] = generateCube(cubeTransform);
  setCubeColour(gray, cubes + 13);
  printf("%d\n", cubes[13].faces[0].faceColour.r);

  // Window configuration
  SDL_Event event;
  SDL_Init(SDL_INIT_VIDEO);
  atexit(SDL_Quit);
  SDL_WM_SetCaption("SDL GL Application", NULL);
  SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective(70,(double)640/480,1,1000);
  glEnable(GL_DEPTH_TEST);

  vector3 cameraPosition = {0, 0, 0};
  vector3 cameraAngle = {5, 0, PI/2};

  while (1) {
    SDL_WaitEvent(&event);

    if (event.key.keysym.sym == SDLK_DOWN && event.key.type == SDL_KEYDOWN) {
      if (cameraAngle.z > 0.000001) {
        cameraAngle.z -= PI / 36;
      }
    }
    else if (event.key.keysym.sym == SDLK_UP && event.key.type == SDL_KEYDOWN) {
      if (cameraAngle.z < PI - 0.000001) {
        cameraAngle.z += PI / 36;
      }
    }
    else if (event.key.keysym.sym == SDLK_RIGHT && event.key.type == SDL_KEYDOWN) {
      cameraAngle.y += PI / 36;
    }
    else if (event.key.keysym.sym == SDLK_LEFT && event.key.type == SDL_KEYDOWN) {
      cameraAngle.y -= PI / 36;
    }

    switch(event.type) {
      case SDL_QUIT:
        exit(0);
        break;
    }

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

    cameraPosition.x = cameraAngle.x * sinf(cameraAngle.z) * cosf(cameraAngle.y);
    cameraPosition.y = cameraAngle.x * sinf(cameraAngle.z) * sinf(cameraAngle.y);
    cameraPosition.z = cameraAngle.x * cosf(cameraAngle.z);

    gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z, 0, 0, 0, 0, 0, 1);

    for (int cubeIndex = 0; cubeIndex < 27; cubeIndex++) {
      drawCube(cubes[cubeIndex]);
    }

    //drawSimpleCube();

    glFlush();
    SDL_GL_SwapBuffers();
  }

  SDL_Quit();
  return 0;
}
