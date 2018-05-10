#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include "graphics.h"

cube generateCube(transform cubeTransform) {
  float xScale = cubeTransform.scale.x;
  float yScale = cubeTransform.scale.y;
  float zScale = cubeTransform.scale.z;

  face topFace = {
    {
      (vector3) {1 * xScale, -1 * yScale, 1 * zScale},
      (vector3) {1 * xScale, 1 * yScale, 1 * zScale},
      (vector3) {-1 * xScale, 1 * yScale, 1 * zScale},
      (vector3) {-1 * xScale, -1 * yScale, 1 * zScale}
    },
    {255, 255, 255}
  };

  face rightFace = {
    {
      (vector3) {1 * xScale, 1 * yScale, 1 * zScale},
      (vector3) {1 * xScale, 1 * yScale, -1 * zScale},
      (vector3) {-1 * xScale, 1 * yScale, -1 * zScale},
      (vector3) {-1 * xScale, 1 * yScale, 1 * zScale}
    },
    {0, 0, 255}
  };

  face frontFace = {
    {
      (vector3) {1 * xScale, -1 * yScale, 1 * zScale},
      (vector3) {1 * xScale, -1 * yScale, -1 * zScale},
      (vector3) {1 * xScale, 1 * yScale, -1 * zScale},
      (vector3) {1 * xScale, 1 * yScale, 1 * zScale}
    },
    {255, 0, 0}
  };

  face leftFace = {
    {
      (vector3) {-1 * xScale, -1 * yScale, 1 * zScale},
      (vector3) {-1 * xScale, -1 * yScale, -1 * zScale},
      (vector3) {1 * xScale, -1 * yScale, -1 * zScale},
      (vector3) {1 * xScale, -1 * yScale, 1 * zScale}
    },
    {0, 255, 0}
  };

  face backFace = {
    {
      (vector3) {-1 * xScale, 1 * yScale, 1 * zScale},
      (vector3) {-1 * xScale, 1 * yScale, -1 * zScale},
      (vector3) {-1 * xScale, -1 * yScale, -1 * zScale},
      (vector3) {-1 * xScale, -1 * yScale, 1 * zScale}
    },
    {255, 165, 0}
  };

  face bottomFace = {
    {
      (vector3) {1 * xScale, 1 * yScale, -1 * zScale},
      (vector3) {1 * xScale, -1 * yScale, -1 * zScale},
      (vector3) {-1 * xScale, -1 * yScale, -1 * zScale},
      (vector3) {-1 * xScale, 1 * yScale, -1 * zScale}
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

    for (int vertexIndex = 0; vertexIndex < 4; vertexIndex++) {
      float x = drawnCube.faces[faceIndex].corners[vertexIndex].x;
      float y = drawnCube.faces[faceIndex].corners[vertexIndex].y;
      float z = drawnCube.faces[faceIndex].corners[vertexIndex].z;

      glVertex3d(x + xOffset, y + yOffset, z + zOffset);
    }
  }

  glEnd();
}

void drawSimpleCube() {
  /*glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );

  gluLookAt(3,4,2,0,0,0,0,0,1);*/

  glBegin(GL_QUADS);

  glColor3ub(20, 20, 20);

  glVertex3d(1,1,1);
  glVertex3d(1,1,-1);
  glVertex3d(-1,1,-1);
  glVertex3d(-1,1,1);

  glVertex3d(1,-1,1);
  glVertex3d(1,-1,-1);
  glVertex3d(1,1,-1);
  glVertex3d(1,1,1);

  glVertex3d(-1,-1,1);
  glVertex3d(-1,-1,-1);
  glVertex3d(1,-1,-1);
  glVertex3d(1,-1,1);

  glVertex3d(-1,1,1);
  glVertex3d(-1,1,-1);
  glVertex3d(-1,-1,-1);
  glVertex3d(-1,-1,1);

  glVertex3d(1,1,-1);
  glVertex3d(1,-1,-1);
  glVertex3d(-1,-1,-1);
  glVertex3d(-1,1,-1);

  glVertex3d(1,-1,1);
  glVertex3d(1,1,1);
  glVertex3d(-1,1,1);
  glVertex3d(-1,-1,1);

  glEnd();

  /*glFlush();
  SDL_GL_SwapBuffers();*/
}
