#ifndef VIEW_H
#define VIEW_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "graphics.h"

#define PI 3.141592653589793

typedef struct _camera {
  vector3 position;
  vector3 angles;
} camera;

typedef struct _rubikview {
  camera mainCamera;
  cube * cubes;
  cube * backFace[9];
  cube * frontFace[9];
  cube * rightFace[9];
  cube * leftFace[9];
  cube * bottomFace[9];
  cube * topFace[9];
} rubikview;

void setWindow();
rubikview generateView();
cube * generateCubes();
void update(camera * mainCamera, cube * cubes);
void closeWindow();

#endif
