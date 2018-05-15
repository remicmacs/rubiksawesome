/**
 * @file graphics.c
 *
 * Problems encountered:
 *
 * ### Unable to correctly apply more than 1 rotation
 *
 * The issue lies in the way we apply the rotations on the cubes. Rotation means
 * a change in orientation and rotations are not commutative (quaternions and
 * rotation matrices).
 *
 * We started by using matrice rotations with two methods: calculated and Using
 * glRotatef. By the time we implemented every rotations, we noticed wrong
 * positioning of some cubes while testing. A proposed workaround would be to
 * keep track of every rotation and apply them in order at every frame.
 * This is power consuming and not ideal from our perspective
 *
 * Another solution would be to use a spherical coordinates system to
 * place the cubes. To make this happens, we will need to register the angles
 * on the cube's generation routine and project the cubes coordinates from the
 * spherical coordinates to the cartesian on every frame.
 *
 * This text above is just some reflexions at the time of this writing.
 * We will commit to keep a track of the code before starting to implement
 * the new method.
 */


#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "graphics.h"


cube generateCube(transform cubeTransform) {

  /** We build the cube by giving it the faces and the transform structure */
  cube mainCube = {
    {
      generateFace(cubeTransform, TOP),
      generateFace(cubeTransform, DOWN),
      generateFace(cubeTransform, FRONT),
      generateFace(cubeTransform, BACK),
      generateFace(cubeTransform, LEFT),
      generateFace(cubeTransform, RIGHT),
    },
    cubeTransform
  };

  return mainCube;
}


face generateFace(transform cubeTransform, enum FaceType faceType) {
  face newFace;
  switch(faceType) {
    case TOP:
      newFace = (face) {
        {
          (vector3) {1, -1, 1},
          (vector3) {1, 1, 1},
          (vector3) {-1, 1, 1},
          (vector3) {-1, -1, 1}
        },
        {255, 255, 255}
      };
      break;
    case DOWN:
      newFace = (face) {
        {
          (vector3) {1, 1, -1},
          (vector3) {1, -1, -1},
          (vector3) {-1, -1, -1},
          (vector3) {-1, 1, -1}
        },
        {255, 255, 0}
      };
      break;
    case FRONT:
      newFace = (face) {
        {
          (vector3) {1, -1, 1},
          (vector3) {1, -1, -1},
          (vector3) {1, 1, -1},
          (vector3) {1, 1, 1}
        },
        {255, 0, 0}
      };
      break;
    case BACK:
      newFace = (face) {
        {
          (vector3) {-1, 1, 1},
          (vector3) {-1, 1, -1},
          (vector3) {-1, -1, -1},
          (vector3) {-1, -1, 1}
        },
        {255, 165, 0}
      };
      break;
    case RIGHT:
      newFace = (face) {
        {
          (vector3) {1, 1, 1},
          (vector3) {1, 1, -1},
          (vector3) {-1, 1, -1},
          (vector3) {-1, 1, 1}
        },
        {0, 0, 255}
      };
      break;
    case LEFT:
      newFace = (face) {
        {
          (vector3) {-1, -1, 1},
          (vector3) {-1, -1, -1},
          (vector3) {1, -1, -1},
          (vector3) {1, -1, 1}
        },
        {0, 255, 0}
      };
      break;
    default:
      break;
  }

  float xOffset = cubeTransform.position.x;
  float yOffset = cubeTransform.position.y;
  float zOffset = cubeTransform.position.z;

  float xScale = cubeTransform.scale.x;
  float yScale = cubeTransform.scale.y;
  float zScale = cubeTransform.scale.z;

  for (int vertexIndex = 0; vertexIndex < 4; vertexIndex++) {
    float x = newFace.corners[vertexIndex].x;
    float y = newFace.corners[vertexIndex].y;
    float z = newFace.corners[vertexIndex].z;

    x = (x * xScale) + xOffset;
    y = (y * yScale) + yOffset;
    z = (z * zScale) + zOffset;

    float faceR = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    float faceTheta = faceR == 0 ? acos(0) : acos(z / faceR);
    float facePhi = atan2(y, x);

    faceR += cubeTransform.delta.x;
    faceTheta += cubeTransform.delta.y;
    facePhi += cubeTransform.delta.z;

    x = faceR * sin(faceTheta) * cos(facePhi);
    y = faceR * sin(faceTheta) * sin(facePhi);
    z = faceR * cos(faceTheta);

    newFace.corners[vertexIndex].x = x;
    newFace.corners[vertexIndex].y = y;
    newFace.corners[vertexIndex].z = z;
  }

  return newFace;
}


void setCubeColour(colour newColour, cube * selectedCube) {
  /** We just change the colour of every faces */
  for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
    selectedCube->faces[faceIndex].faceColour = newColour;
  }
}

void drawCube(cube drawnCube, bool debug) {
  /** We draw the faces */
  for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
    drawFace(drawnCube.faces[faceIndex], debug);
  }
}

void drawFace(face drawnFace, bool debug) {
  colour faceColour;

  /**
   * If the cube is to be debugged, it will be displayed in magenta
   */
  if (debug) {
    faceColour = (colour) {255, 0, 255};
  } else {
    faceColour = drawnFace.faceColour;
  }

  /** We set the colour of the vertices */
  glColor3ub(faceColour.r, faceColour.g, faceColour.b);

  glBegin(GL_QUADS);
  for (int vertexIndex = 0; vertexIndex < 4; vertexIndex++) {
    float x = drawnFace.corners[vertexIndex].x;
    float y = drawnFace.corners[vertexIndex].y;
    float z = drawnFace.corners[vertexIndex].z;
    glVertex3d(x, y, z);
  }
  glEnd();
}


void rotateFaceY(face * currentFace, float angle, bool ccw) {
  for (int cornerIndex = 0; cornerIndex < 4; cornerIndex++) {
    float x = currentFace->corners[cornerIndex].x;
    float z = currentFace->corners[cornerIndex].z;
    float yRotation = ccw == true ? - angle : angle;

    float xPrime = z * sinf(yRotation) + x * cosf(yRotation);
    float zPrime = z * cosf(yRotation) - x * sinf(yRotation);

    currentFace->corners[cornerIndex].x = xPrime;
    currentFace->corners[cornerIndex].z = zPrime;
  }
}


void rotateFaceZ(face * currentFace, float angle, bool ccw) {
  for (int cornerIndex = 0; cornerIndex < 4; cornerIndex++) {
    float x = currentFace->corners[cornerIndex].x;
    float y = currentFace->corners[cornerIndex].y;
    float zRotation = ccw == true ? - angle : angle;

    float xPrime = x * cosf(zRotation) - y * sinf(zRotation);
    float yPrime = x * sinf(zRotation) + y * cosf(zRotation);

    currentFace->corners[cornerIndex].x = xPrime;
    currentFace->corners[cornerIndex].y = yPrime;
  }
}


void rotateFaceX(face * currentFace, float angle, bool ccw) {
  for (int cornerIndex = 0; cornerIndex < 4; cornerIndex++) {
    float z = currentFace->corners[cornerIndex].z;
    float y = currentFace->corners[cornerIndex].y;
    float xRotation = ccw == true ? - angle : angle;

    float zPrime = y * sinf(xRotation) + z * cosf(xRotation);
    float yPrime = y * cosf(xRotation) - z * sinf(xRotation);

    currentFace->corners[cornerIndex].z = zPrime;
    currentFace->corners[cornerIndex].y = yPrime;
  }
}


void rotateFaceData(cube ** rotatedFace, bool ccw) {
  if (ccw) {
    // Here is counterclockwise
    cube * tempCube;

    // Rotate corners
    tempCube = rotatedFace[0];
    rotatedFace[0] = rotatedFace[6];
    rotatedFace[6] = rotatedFace[8];
    rotatedFace[8] = rotatedFace[2];
    rotatedFace[2] = tempCube;

    // Rotate edges
    tempCube = rotatedFace[1];
    rotatedFace[1] = rotatedFace[3];
    rotatedFace[3] = rotatedFace[7];
    rotatedFace[7] = rotatedFace[5];
    rotatedFace[5] = tempCube;
  } else {
    cube * tempCube;

    // Rotate corners
    tempCube = rotatedFace[0];
    rotatedFace[0] = rotatedFace[2];
    rotatedFace[2] = rotatedFace[8];
    rotatedFace[8] = rotatedFace[6];
    rotatedFace[6] = tempCube;

    // Rotate edges
    tempCube = rotatedFace[1];
    rotatedFace[1] = rotatedFace[5];
    rotatedFace[5] = rotatedFace[7];
    rotatedFace[7] = rotatedFace[3];
    rotatedFace[3] = tempCube;
  }
}
