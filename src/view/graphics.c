/**
 * @file graphics.c
 *
 * Problems encountered:
 *
 * ### Unable to correctly apply more than 1 rotation
 *
 * The issue lies in the way we apply the rotations on the cubes. Rotation means
 * a change in orientation and when using rotation matrices they are not
 * commutative.
 *
 * We started by using matrice rotations with two methods: calculated and using
 * glRotatef. By the time we implemented every rotations, we noticed wrong
 * positioning of some cubes while testing. A proposed workaround would be to
 * keep track of every rotation and apply them in order at every frame.
 * This is power consuming and not ideal from our perspective. Another solution
 * is to use quaternions, which are complex objects to manipulate. We'll settle
 * on a simple solution.
 *
 * The adopted solution is to save the vertices positions on generation and,
 * each time a rotation is called, rotate them around the desire axis and
 * save the new position. Since our moves are all simple rotations around an
 * axis, we'll keep committing to the KISS principle.
 */


#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"


rubikcube * generateRubikCube() {
  rubikcube * rubikCube;
  rubikCube = (rubikcube *) malloc(sizeof(rubikcube));

  /** AATMYNTA (Always Allocate The Memory You Need To Allocate) */
  cube3d **** cubes = (cube3d ****) malloc(3 * sizeof(cube3d ***));
  for (int zIndex = -1; zIndex < 2; zIndex++) {
    cube3d *** yCubes = (cube3d ***) malloc(3 * sizeof(cube3d **));
    for (int yIndex = -1; yIndex <2; yIndex++) {
      cube3d ** xCubes = (cube3d **) malloc(3 * sizeof(cube3d *));
      for (int xIndex = -1; xIndex < 2; xIndex++) {
        transform cubeTransform = {
          (vector3) {(float)zIndex, (float)yIndex, (float)xIndex},
          (vector3) {0, 0, 0},
          (vector3) {0, 0, 0},
          (vector3) {0.45, 0.45, 0.45}
        };

        xCubes[xIndex + 1] = (cube3d *) malloc(sizeof(cube3d));
        *xCubes[xIndex + 1] = generateCube(cubeTransform);
      }
      yCubes[yIndex + 1] = xCubes;
    }
    cubes[zIndex + 1] = yCubes;
  }

  rubikCube->cubes = cubes;
  return rubikCube;
}


cube3d generateCube(transform cubeTransform) {

  /** We build the cube by giving it the faces and the transform structure */
  cube3d mainCube = {
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
        {0, 0, 1},
        {238, 238, 238}
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
        {0, 0, -1},
        {255, 204, 0}
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
        {1, 0, 0},
        {204, 0, 0}
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
        {-1, 0, 0},
        {233, 100, 0}
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
        {0, 1, 0},
        {34, 85, 221}
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
        {0, -1, 0},
        {0, 153, 34}
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


void generateTexture(GLuint * textureId, const char * url) {
  SDL_Surface * surf = IMG_Load(url);
  glGenTextures(1, textureId);
  glBindTexture(GL_TEXTURE_2D, *textureId);
  int Mode = GL_RGBA;
  if(surf->format->BytesPerPixel == 4) {
      Mode = GL_RGBA;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, Mode, surf->w, surf->h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, surf->pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  SDL_FreeSurface(surf);
}


void generateCubemapTexture(GLuint * textureId) {
  glGenTextures(1, textureId);
  glBindTexture(GL_TEXTURE_CUBE_MAP, *textureId);

  const char * files[22] = {
    "res/skybox/right.png",
    "res/skybox/left.png",
    "res/skybox/top.png",
    "res/skybox/bottom.png",
    "res/skybox/front.png",
    "res/skybox/back.png"
  };

  for (int imageIndex = 0; imageIndex < 6; imageIndex++) {
    SDL_Surface * surf = IMG_Load(files[imageIndex]);

    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB + imageIndex, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surf->pixels);

    SDL_FreeSurface(surf);
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}


image generateInstructions(enum FaceType faceType) {
  image newInstruction;
  switch(faceType) {
    case TOP:
      newInstruction.corners[0] = (vector3) {-1, 1, 2.3};
      newInstruction.corners[1] = (vector3) {1, 1, 2.3};
      newInstruction.corners[2] = (vector3) {1, -1, 2.3};
      newInstruction.corners[3] = (vector3) {-1, -1, 2.3};
      newInstruction.normal = (vector3) {0, 0, 1};
      generateTexture(&newInstruction.imageTexture.id, "res/up.png");
      generateTexture(&newInstruction.imageTexture.ccwId, "res/UP.png");
      generateTexture(&newInstruction.imageTexture.id2, "res/up2.png");
      generateTexture(&newInstruction.imageTexture.ccwId2, "res/UP2.png");
      break;
    case DOWN:
      newInstruction.corners[0] = (vector3) {-1, -1, -2.3};
      newInstruction.corners[1] = (vector3) {1, -1, -2.3};
      newInstruction.corners[2] = (vector3) {1, 1, -2.3};
      newInstruction.corners[3] = (vector3) {-1, 1, -2.3};
      newInstruction.normal = (vector3) {0, 0, -1};
      generateTexture(&newInstruction.imageTexture.id, "res/down.png");
      generateTexture(&newInstruction.imageTexture.ccwId, "res/DOWN.png");
      generateTexture(&newInstruction.imageTexture.id2, "res/down2.png");
      generateTexture(&newInstruction.imageTexture.ccwId2, "res/DOWN2.png");
      break;
    case FRONT:
      newInstruction.corners[0] = (vector3) {-1, -2.3, 1};
      newInstruction.corners[1] = (vector3) {1, -2.3, 1};
      newInstruction.corners[2] = (vector3) {1, -2.3, -1};
      newInstruction.corners[3] = (vector3) {-1, -2.3, -1};
      newInstruction.normal = (vector3) {0, -1, 0};
      generateTexture(&newInstruction.imageTexture.id, "res/front.png");
      generateTexture(&newInstruction.imageTexture.ccwId, "res/FRONT.png");
      generateTexture(&newInstruction.imageTexture.id2, "res/front2.png");
      generateTexture(&newInstruction.imageTexture.ccwId2, "res/FRONT2.png");
      break;
    case BACK:
      newInstruction.corners[0] = (vector3) {1, 2.3, 1};
      newInstruction.corners[1] = (vector3) {-1, 2.3, 1};
      newInstruction.corners[2] = (vector3) {-1, 2.3, -1};
      newInstruction.corners[3] = (vector3) {1, 2.3, -1};
      newInstruction.normal = (vector3) {0, 1, 0};
      generateTexture(&newInstruction.imageTexture.id, "res/back.png");
      generateTexture(&newInstruction.imageTexture.ccwId, "res/BACK.png");
      generateTexture(&newInstruction.imageTexture.id2, "res/back2.png");
      generateTexture(&newInstruction.imageTexture.ccwId2, "res/BACK2.png");
      break;
    case RIGHT:
      newInstruction.corners[0] = (vector3) {2.3, -1, 1};
      newInstruction.corners[1] = (vector3) {2.3, 1, 1};
      newInstruction.corners[2] = (vector3) {2.3, 1, -1};
      newInstruction.corners[3] = (vector3) {2.3, -1, -1};
      newInstruction.normal = (vector3) {1, 0, 0};
      generateTexture(&newInstruction.imageTexture.id, "res/right.png");
      generateTexture(&newInstruction.imageTexture.ccwId, "res/RIGHT.png");
      generateTexture(&newInstruction.imageTexture.id2, "res/right2.png");
      generateTexture(&newInstruction.imageTexture.ccwId2, "res/RIGHT2.png");
      break;
    case LEFT:
      newInstruction.corners[0] = (vector3) {-2.3, 1, 1};
      newInstruction.corners[1] = (vector3) {-2.3, -1, 1};
      newInstruction.corners[2] = (vector3) {-2.3, -1, -1};
      newInstruction.corners[3] = (vector3) {-2.3, 1, -1};
      newInstruction.normal = (vector3) {-1, 0, 0};
      generateTexture(&newInstruction.imageTexture.id, "res/left.png");
      generateTexture(&newInstruction.imageTexture.ccwId, "res/LEFT.png");
      generateTexture(&newInstruction.imageTexture.id2, "res/left2.png");
      generateTexture(&newInstruction.imageTexture.ccwId2, "res/LEFT2.png");
      break;
    default:
      break;
  }
  return newInstruction;
}


void setCubeColour(colour newColour, cube3d * selectedCube) {
  /** We just change the colour of every faces */
  for (int faceIndex = 0; faceIndex < 6; faceIndex++) {
    selectedCube->faces[faceIndex].faceColour = newColour;
  }
}

void drawCube(cube3d drawnCube, bool debug) {
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
  glNormal3f(drawnFace.normal.x, drawnFace.normal.y, drawnFace.normal.z);
  for (int vertexIndex = 0; vertexIndex < 4; vertexIndex++) {
    float x = drawnFace.corners[vertexIndex].x;
    float y = drawnFace.corners[vertexIndex].y;
    float z = drawnFace.corners[vertexIndex].z;

    glVertex3d(x, y, z);
  }
  glEnd();
}


void drawInstruction(image drawnInstruction, bool ccw, bool two) {
  GLuint textureId;
  if (ccw && two) {
    textureId = drawnInstruction.imageTexture.ccwId2;
  } else if (ccw && !two) {
    textureId = drawnInstruction.imageTexture.ccwId;
  } else if (!ccw && two) {
    textureId = drawnInstruction.imageTexture.id2;
  } else {
    textureId = drawnInstruction.imageTexture.id;
  }

  glBindTexture(GL_TEXTURE_2D, textureId);

  glColor4ub(255, 255, 255, 255);

  float corners[4][2] = {
    {0, 0},
    {1, 0},
    {1, 1},
    {0, 1}
  };

  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
  glNormal3f(drawnInstruction.normal.x, drawnInstruction.normal.y, drawnInstruction.normal.z);

  for (int vertexIndex = 0; vertexIndex < 4; vertexIndex++) {
    float x = drawnInstruction.corners[vertexIndex].x;
    float y = drawnInstruction.corners[vertexIndex].y;
    float z = drawnInstruction.corners[vertexIndex].z;

    float xMap = corners[vertexIndex][0];
    float yMap = corners[vertexIndex][1];

    glTexCoord2f(xMap, yMap);
    glVertex3d(x, y, z);
  }
  glEnd();
  glDisable(GL_TEXTURE_2D);
}


void drawSkybox(GLuint textureId) {
  // Taille du cube
  float t = 500.0f;

  // Utilisation de la texture CubeMap
  glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, textureId);

  glEnable(GL_TEXTURE_CUBE_MAP_ARB);
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glDepthMask(GL_FALSE);

  glColor3ub(255, 255, 255);

  // Rendu de la géométrie
  glBegin(GL_TRIANGLE_STRIP);			// X Négatif
  	glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t);
  	glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
  	glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
  	glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);			// X Positif
  	glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
  	glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
  	glTexCoord3f(t,t,-t); glVertex3f(t,t,-t);
  	glTexCoord3f(t,t,t); glVertex3f(t,t,t);
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);			// Y Négatif
  	glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t);
  	glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
  	glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
  	glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);			// Y Positif
  	glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
  	glTexCoord3f(t,t,-t); glVertex3f(t,t,-t);
  	glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
  	glTexCoord3f(t,t,t); glVertex3f(t,t,t);
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);			// Z Négatif
  	glTexCoord3f(-t,-t,-t); glVertex3f(-t,-t,-t);
  	glTexCoord3f(t, -t,-t); glVertex3f(t,-t,-t);
  	glTexCoord3f(-t,t,-t); glVertex3f(-t,t,-t);
  	glTexCoord3f(t,t,-t); glVertex3f(t,t,-t);
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);			// Z Positif
  	glTexCoord3f(-t,-t,t); glVertex3f(-t,-t,t);
  	glTexCoord3f(-t,t,t); glVertex3f(-t,t,t);
  	glTexCoord3f(t,-t,t); glVertex3f(t,-t,t);
  	glTexCoord3f(t,t,t); glVertex3f(t,t,t);
  glEnd();

  glDepthMask(GL_TRUE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glDisable(GL_TEXTURE_CUBE_MAP_ARB);
}


void rotateFaceY(face * currentFace, float angle, bool ccw) {
  float yRotation = ccw == true ? - angle : angle;
  float sinRotation = sinf(yRotation);
  float cosRotation = cosf(yRotation);
  for (int cornerIndex = 0; cornerIndex < 4; cornerIndex++) {
    float x = currentFace->corners[cornerIndex].x;
    float z = currentFace->corners[cornerIndex].z;

    float xPrime = z * sinRotation + x * cosRotation;
    float zPrime = z * cosRotation - x * sinRotation;

    currentFace->corners[cornerIndex].x = xPrime;
    currentFace->corners[cornerIndex].z = zPrime;
  }

  float xNormal = currentFace->normal.x;
  float zNormal = currentFace->normal.z;

  float xNormalPrime = zNormal * sinRotation + xNormal * cosRotation;
  float zNormalPrime = zNormal * cosRotation - xNormal * sinRotation;

  currentFace->normal.x = xNormalPrime;
  currentFace->normal.z = zNormalPrime;
}


void rotateFaceZ(face * currentFace, float angle, bool ccw) {
  float zRotation = ccw == true ? - angle : angle;
  float sinRotation = sinf(zRotation);
  float cosRotation = cosf(zRotation);
  for (int cornerIndex = 0; cornerIndex < 4; cornerIndex++) {
    float x = currentFace->corners[cornerIndex].x;
    float y = currentFace->corners[cornerIndex].y;

    float xPrime = x * cosRotation - y * sinRotation;
    float yPrime = x * sinRotation + y * cosRotation;

    currentFace->corners[cornerIndex].x = xPrime;
    currentFace->corners[cornerIndex].y = yPrime;
  }

  float xNormal = currentFace->normal.x;
  float yNormal = currentFace->normal.y;

  float xNormalPrime = xNormal * cosRotation - yNormal * sinRotation;
  float yNormalPrime = xNormal * sinRotation + yNormal * cosRotation;

  currentFace->normal.x = xNormalPrime;
  currentFace->normal.y = yNormalPrime;
}


void rotateFaceX(face * currentFace, float angle, bool ccw) {
  float xRotation = ccw == true ? - angle : angle;
  float sinRotation = sinf(xRotation);
  float cosRotation = cosf(xRotation);
  for (int cornerIndex = 0; cornerIndex < 4; cornerIndex++) {
    float z = currentFace->corners[cornerIndex].z;
    float y = currentFace->corners[cornerIndex].y;

    float zPrime = y * sinRotation + z * cosRotation;
    float yPrime = y * cosRotation - z * sinRotation;

    currentFace->corners[cornerIndex].z = zPrime;
    currentFace->corners[cornerIndex].y = yPrime;
  }

  float zNormal = currentFace->normal.z;
  float yNormal = currentFace->normal.y;

  float zNormalPrime = yNormal * sinRotation + zNormal * cosRotation;
  float yNormalPrime = yNormal * cosRotation - zNormal * sinRotation;

  currentFace->normal.z = zNormalPrime;
  currentFace->normal.y = yNormalPrime;
}
