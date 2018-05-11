#ifndef GRAPHICS_H
#define GRAPHICS_H

typedef struct _colour {
  int r;
  int g;
  int b;
} colour;

typedef struct _vector3 {
  float x;
  float y;
  float z;
} vector3;

typedef struct _face {
  vector3 corners[4];
  colour faceColour;
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
void setCubeColour(colour newColour, cube * selectedCube);
void drawCube(cube drawnCube);

#endif
