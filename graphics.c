#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include "graphics.h"

cube generateCube(transform cubeTransform) {
  float xScale = cubeTransform.scale.x;
  float yScale = cubeTransform.scale.y;
  float zScale = cubeTransform.scale.z;

  // Top face
  face topFace = {
    {
      (vector3) {1 * xScale, -1 * yScale, 1 * zScale},
      (vector3) {1 * xScale, 1 * yScale, 1 * zScale},
      (vector3) {-1 * xScale, 1 * yScale, 1 * zScale},
      (vector3) {-1 * xScale, -1 * yScale, 1 * zScale}
    }
  };

  face frontFace = {
    {
      (vector3) {1 * xScale, 1 * yScale, 1 * zScale},
      (vector3) {1 * xScale, 1 * yScale, -1 * zScale},
      (vector3) {-1 * xScale, 1 * yScale, -1 * zScale},
      (vector3) {-1 * xScale, 1 * yScale, 1 * zScale}
    }
  };

  face leftFace = {
    {
      (vector3) {1 * xScale, -1 * yScale, 1 * zScale},
      (vector3) {1 * xScale, -1 * yScale, -1 * zScale},
      (vector3) {1 * xScale, 1 * yScale, -1 * zScale},
      (vector3) {1 * xScale, 1 * yScale, 1 * zScale}
    }
  };

  face backFace = {
    {
      (vector3) {-1 * xScale, -1 * yScale, 1 * zScale},
      (vector3) {-1 * xScale, -1 * yScale, -1 * zScale},
      (vector3) {1 * xScale, -1 * yScale, -1 * zScale},
      (vector3) {1 * xScale, -1 * yScale, 1 * zScale}
    }
  };

  face rightFace = {
    {
      (vector3) {-1 * xScale, 1 * yScale, 1 * zScale},
      (vector3) {-1 * xScale, 1 * yScale, -1 * zScale},
      (vector3) {-1 * xScale, -1 * yScale, -1 * zScale},
      (vector3) {-1 * xScale, -1 * yScale, 1 * zScale}
    }
  };

  face bottomFace = {
    {
      (vector3) {1 * xScale, 1 * yScale, -1 * zScale},
      (vector3) {1 * xScale, -1 * yScale, -1 * zScale},
      (vector3) {-1 * xScale, -1 * yScale, -1 * zScale},
      (vector3) {-1 * xScale, 1 * yScale, -1 * zScale}
    }
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

void drawCube(cube drawnCube) {
  glBegin(GL_QUADS);

  for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
    glColor3ub((faceIndex + 1) * (255 / 6), 0, 0);

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
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );

  gluLookAt(3,4,2,0,0,0,0,0,1);

  glBegin(GL_QUADS);

  glColor3ub(255,0,0); //face rouge
  glVertex3d(1,1,1);
  glVertex3d(1,1,-1);
  glVertex3d(-1,1,-1);
  glVertex3d(-1,1,1);

  glColor3ub(0,255,0); //face verte
  glVertex3d(1,-1,1);
  glVertex3d(1,-1,-1);
  glVertex3d(1,1,-1);
  glVertex3d(1,1,1);

  glColor3ub(0,0,255); //face bleue
  glVertex3d(-1,-1,1);
  glVertex3d(-1,-1,-1);
  glVertex3d(1,-1,-1);
  glVertex3d(1,-1,1);

  glColor3ub(255,255,0); //face jaune
  glVertex3d(-1,1,1);
  glVertex3d(-1,1,-1);
  glVertex3d(-1,-1,-1);
  glVertex3d(-1,-1,1);

  glColor3ub(0,255,255); //face cyan
  glVertex3d(1,1,-1);
  glVertex3d(1,-1,-1);
  glVertex3d(-1,-1,-1);
  glVertex3d(-1,1,-1);

  glColor3ub(255,0,255); //face magenta
  glVertex3d(1,-1,1);
  glVertex3d(1,1,1);
  glVertex3d(-1,1,1);
  glVertex3d(-1,-1,1);

  glEnd();

  glFlush();
  SDL_GL_SwapBuffers();
}
