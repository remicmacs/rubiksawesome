#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include "graphics.h"
#include <math.h>

cube generateCube(transform cubeTransform) {
  face topFace = {
    {
      (vector3) {1, -1, 1},
      (vector3) {1, 1, 1},
      (vector3) {-1, 1, 1},
      (vector3) {-1, -1, 1}
    },
    {255, 255, 255}
  };

  face rightFace = {
    {
      (vector3) {1, 1, 1},
      (vector3) {1, 1, -1},
      (vector3) {-1, 1, -1},
      (vector3) {-1, 1, 1}
    },
    {0, 0, 255}
  };

  face frontFace = {
    {
      (vector3) {1, -1, 1},
      (vector3) {1, -1, -1},
      (vector3) {1, 1, -1},
      (vector3) {1, 1, 1}
    },
    {255, 0, 0}
  };

  face leftFace = {
    {
      (vector3) {-1, -1, 1},
      (vector3) {-1, -1, -1},
      (vector3) {1, -1, -1},
      (vector3) {1, -1, 1}
    },
    {0, 255, 0}
  };

  face backFace = {
    {
      (vector3) {-1, 1, 1},
      (vector3) {-1, 1, -1},
      (vector3) {-1, -1, -1},
      (vector3) {-1, -1, 1}
    },
    {255, 165, 0}
  };

  face bottomFace = {
    {
      (vector3) {1, 1, -1},
      (vector3) {1, -1, -1},
      (vector3) {-1, -1, -1},
      (vector3) {-1, 1, -1}
    },
    {255, 255, 0}
  };

  cube mainCube = {
    {
      topFace,
      bottomFace,
      frontFace,
      backFace,
      leftFace,
      rightFace
    },
    cubeTransform
  };

  return mainCube;
}

void setCubeColour(colour newColour, cube * selectedCube) {
  for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
    selectedCube->faces[faceIndex].faceColour = newColour;
  }
}

void drawCube(cube drawnCube) {
  glBegin(GL_QUADS);

  for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
    colour faceColour = drawnCube.faces[faceIndex].faceColour;
    glColor3ub(faceColour.r, faceColour.g, faceColour.b);

    float xOffset = drawnCube.cubeTransform.position.x;
    float yOffset = drawnCube.cubeTransform.position.y;
    float zOffset = drawnCube.cubeTransform.position.z;

    float xScale = drawnCube.cubeTransform.scale.x;
    float yScale = drawnCube.cubeTransform.scale.y;
    float zScale = drawnCube.cubeTransform.scale.z;

    float xRotation = drawnCube.cubeTransform.rotation.x;
    float yRotation = drawnCube.cubeTransform.rotation.y;
    float zRotation = drawnCube.cubeTransform.rotation.z;

    for (int vertexIndex = 0; vertexIndex < 4; vertexIndex++) {
      float x = drawnCube.faces[faceIndex].corners[vertexIndex].x;
      float y = drawnCube.faces[faceIndex].corners[vertexIndex].y;
      float z = drawnCube.faces[faceIndex].corners[vertexIndex].z;

      x = (x * xScale) + xOffset;
      y = (y * yScale) + yOffset;
      z = (z * zScale) + zOffset;

      float xPrime = x * cosf(zRotation) - y * sinf(zRotation);
      float yPrime = x * sinf(zRotation) + y * cosf(zRotation);
      float zPrime = z;

      float xPrime2 = xPrime;
      float yPrime2 = yPrime * cosf(xRotation) - zPrime * sinf(xRotation);
      float zPrime2 = yPrime * sinf(xRotation) + zPrime * cosf(xRotation);

      float xPrime3 = zPrime2 * sinf(yRotation) + xPrime2 * cosf(yRotation);
      float yPrime3 = yPrime2;
      float zPrime3 = zPrime2 * cosf(yRotation) - xPrime2 * sinf(yRotation);

      glVertex3d(xPrime3, yPrime3, zPrime3);
    }
  }

  glEnd();
}
