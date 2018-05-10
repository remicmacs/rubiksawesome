#ifndef GRAPHICS_H
#define GRAPHICS_H

typedef struct _vector3 {
  float x;
  float y;
  float z;
} vector3;

typedef struct _face {
  vector3 corners[4];
} face;

typedef struct _transform {
  vector3 position;
  vector3 rotation;
  vector3 scale;
} transform;

typedef struct _cube {
  face faces[6];
  transform cubeTransform;
} cube;

cube generateCube(transform cubeTransform);
void drawCube(cube drawnCube);
void drawSimpleCube();

#endif
