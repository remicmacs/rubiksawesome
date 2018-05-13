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

  /** The Top face is white */
  face topFace = {
    {
      (vector3) {1, -1, 1},
      (vector3) {1, 1, 1},
      (vector3) {-1, 1, 1},
      (vector3) {-1, -1, 1}
    },
    {255, 255, 255}
  };

  /** The right face is blue */
  face rightFace = {
    {
      (vector3) {1, 1, 1},
      (vector3) {1, 1, -1},
      (vector3) {-1, 1, -1},
      (vector3) {-1, 1, 1}
    },
    {0, 0, 255}
  };

  /** The Front face is red */
  face frontFace = {
    {
      (vector3) {1, -1, 1},
      (vector3) {1, -1, -1},
      (vector3) {1, 1, -1},
      (vector3) {1, 1, 1}
    },
    {255, 0, 0}
  };

  /** The Left face is green */
  face leftFace = {
    {
      (vector3) {-1, -1, 1},
      (vector3) {-1, -1, -1},
      (vector3) {1, -1, -1},
      (vector3) {1, -1, 1}
    },
    {0, 255, 0}
  };

  /** The Back face is orange */
  face backFace = {
    {
      (vector3) {-1, 1, 1},
      (vector3) {-1, 1, -1},
      (vector3) {-1, -1, -1},
      (vector3) {-1, -1, 1}
    },
    {255, 165, 0}
  };

  /** The Down face is yellow */
  face bottomFace = {
    {
      (vector3) {1, 1, -1},
      (vector3) {1, -1, -1},
      (vector3) {-1, -1, -1},
      (vector3) {-1, 1, -1}
    },
    {255, 255, 0}
  };

  /** We build the cube by giving it the faces and the transform structure */
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
  /** We just change the colour of every faces */
  for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
    selectedCube->faces[faceIndex].faceColour = newColour;
  }
}

void drawCube(cube drawnCube, bool debug) {
  /**
   * Using glRotatef
   * This solution doesn't seem to be good, see the header of the file for
   * more information. Uncomment to try it. There is another block below to
   * uncomment. Comment it if you're trying the other method.
   */
  /***************************************************************************/
  // float xOffset = drawnCube.cubeTransform.position.x;
  // float yOffset = drawnCube.cubeTransform.position.y;
  // float zOffset = drawnCube.cubeTransform.position.z;

  // float xRotation = drawnCube.cubeTransform.rotation.x;
  // float yRotation = drawnCube.cubeTransform.rotation.y;
  // float zRotation = drawnCube.cubeTransform.rotation.z;

  /** We store the current matrix transformation */
  // glPushMatrix();

  /** We rotate z, y, and x in that order */
  // glRotatef(zRotation * (180 / PI), 0, 0, 1);
  // glRotatef(yRotation * (180 / PI), 0, 1, 0);
  // glRotatef(xRotation * (180 / PI), 1, 0, 0);

  /** We translate the cube to where it will be */
  // glTranslatef(xOffset, yOffset, zOffset);*/
  /***************************************************************************/

  /** And we draw the faces */
  for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
    drawFace(drawnCube.faces[faceIndex], drawnCube.cubeTransform.position, drawnCube.cubeTransform.rotation, drawnCube.cubeTransform.scale, debug);
  }

  /**
   * Uncomment this as well for the openGL rotation method. More below.
   */
  /***************************************************************************/
  // glPopMatrix();
  /***************************************************************************/
}

void drawFace(face drawnFace, vector3 position, vector3 rotation, vector3 scale, bool debug) {
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

  float xScale = scale.x;
  float yScale = scale.y;
  float zScale = scale.z;

  float xOffset = position.x;
  float yOffset = position.y;
  float zOffset = position.z;

  float xRotation = rotation.x;
  float yRotation = rotation.y;
  float zRotation = rotation.z;

  glBegin(GL_QUADS);
  for (int vertexIndex = 0; vertexIndex < 4; vertexIndex++) {
    float x = drawnFace.corners[vertexIndex].x;
    float y = drawnFace.corners[vertexIndex].y;
    float z = drawnFace.corners[vertexIndex].z;

    /**
     * Uncomment this for glRotatef. Now we have to disable the calculated
     * method. See below.
     */
    /**************************************************************************/
    // x = x * xScale;
    // y = y * yScale;
    // z = z * zScale;

    // glVertex3d(x, y, z);

    /**
     * Comment this if you're trying the openGL rotation method. You're good
     * to go !
     */
    /**************************************************************************/
    x = (x * xScale) + xOffset;
    y = (y * yScale) + yOffset;
    z = (z * zScale) + zOffset;

    /**
     * We apply the z-axis rotation
     */
    float xPrime = x * cosf(zRotation) - y * sinf(zRotation);
    float yPrime = x * sinf(zRotation) + y * cosf(zRotation);
    float zPrime = z;

    /**
     * We apply the y-axis rotation
     */
    float xPrime2 = xPrime;
    float yPrime2 = yPrime * cosf(xRotation) - zPrime * sinf(xRotation);
    float zPrime2 = yPrime * sinf(xRotation) + zPrime * cosf(xRotation);

    /**
     * We apply the x-axis rotation
     */
    float xPrime3 = zPrime2 * sinf(yRotation) + xPrime2 * cosf(yRotation);
    float yPrime3 = yPrime2;
    float zPrime3 = zPrime2 * cosf(yRotation) - xPrime2 * sinf(yRotation);
    /**************************************************************************/
    /*
     * Stop commenting here !
     */

    /** We draw the vertex */
    glVertex3d(xPrime3, yPrime3, zPrime3);
  }
  glEnd();
}
