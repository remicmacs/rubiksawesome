/**
 * @file view.c
 */


#include "view.h"


static SDL_Keycode konamiCode[] = {SDLK_UP, SDLK_UP, SDLK_DOWN, SDLK_DOWN,
                                   SDLK_LEFT, SDLK_RIGHT, SDLK_LEFT, SDLK_RIGHT,
                                   SDLK_b, SDLK_a};


void setSDL() {
  /** Initialize SDL */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    exit(1);
  }

  /** Enabling SDL multisampling (antialiasing) */
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

  /** Intialize sound */
  if (Mix_OpenAudio(24000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
    printf("%s", Mix_GetError());
    exit(2);
  }
  Mix_AllocateChannels(2);

  /** Display SDL version */
  SDL_version sdlVersion;
  SDL_VERSION(&sdlVersion);
  printf("SDL version: %d.%d.%d\n", sdlVersion.major, sdlVersion.minor, sdlVersion.patch);
}


/******************************************************************************
 * GENERATE VIEW ELEMENTS
 ******************************************************************************/


camera generateCamera() {
  /** Set the camera starting position */
  camera mainCamera;
  mainCamera.position = (vector3) {0, 0, 0};
  mainCamera.angles = (vector3) {8, - 3 * PI / 4, PI / 3};
  mainCamera.position = polarToCartesian(mainCamera.angles);

  mainCamera.rotate = &rotateCamera;
  mainCamera.zoom = &zoomCamera;

  return mainCamera;
}


rubikview generateView() {
  rubikview mainView;

  /*
   *  Set the window title and set the window size, the colour depth and
   *  context to OpenGL
   */
  mainView.mainWindow = SDL_CreateWindow("Rubiksawesome",
                                         SDL_WINDOWPOS_UNDEFINED,
                                         SDL_WINDOWPOS_UNDEFINED,
                                         800, 600, SDL_WINDOW_OPENGL);
  SDL_CreateRenderer(mainView.mainWindow, -1, 0);
  SDL_GL_CreateContext(mainView.mainWindow);

  /** Set up of the projection matrix to use perspective */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, (double)800 / 600, 1, 1000);

  /** Enable depth testing (allows objects to hide each others) */
  glEnable(GL_DEPTH_TEST);

  /*
   * Enable transparency by enabling blending between alpha channel and
   * previous alpha channel
   */
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  /** Enable lighting */
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  /** Enable OpenGL multisampling (antialiasing) */
  glEnable(GL_MULTISAMPLE);

  /** Create light components and assign them to GL_LIGHT0 */
  GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
  GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
  GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
  GLfloat position[] = { -1.0f, 0, 0, 1.0f };
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
  glLightfv(GL_LIGHT0, GL_POSITION, position);

  /** Print OpenGL version */
  printf("OpenGL version: %s\n", glGetString(GL_VERSION));
  fflush(stdout);

  /*
   * Create the cube and assign the camera, the rubik's cube and an empty
   * animations list
   */
  mainView.texStore = generateTextureStore();
  mainView.sndStore = generateSoundStore();
  mainView.mainCamera = generateCamera();
  mainView.rubikCube = generateRubikCube();
  mainView.animStack = NULL;
  mainView.gameWon = false;
  mainView.konamiCount = 0;

  /*
   * Setting the parameters for the solving window display
   */
  mainView.windowToDisplay = false;
  mainView.windowDisplayed = false;
  mainView.solveWindow = NULL;

  /*
   * Generates instructions and add them to the view (hidden by default)
   */
  enum FaceType faces[6] = {FRONT, RIGHT, TOP, DOWN, BACK, LEFT};
  for (int index = 0; index < 6; index++) {
    mainView.instructions[index] = generateInstruction(faces[index],
                                                       mainView.texStore);
  }
  mainView.instructionsDisplayed = false;

  /*
   * Functions bindings
   * update() -> update()
   * animate() -> parseOrder()
   */
  mainView.update = &update;
  mainView.animate = &parseOrder;

  return mainView;
}


/******************************************************************************
 * UPDATES AND OPENINGS
 ******************************************************************************/


void showHelpWindow(rubikview * mainView) {
  /** Set the flags */
  mainView->windowToDisplay = false;
  mainView->windowDisplayed = true;

  /** Destroy the current window if it exists */
  SDL_DestroyWindow(mainView->solveWindow);

  /** Create the new window */
  mainView->solveWindow = SDL_CreateWindow("Help",
                                           SDL_WINDOWPOS_UNDEFINED,
                                           SDL_WINDOWPOS_UNDEFINED,
                                           800, 100, 0);
}


void update(rubikview * mainView, mvqueue moveQueue, mvstack moveStack, mvqueue solveMoves) {
  Uint32 startTime = SDL_GetTicks();

  camera * mainCamera = &(mainView->mainCamera);
  bool imageChanged = false;

  /*
   * Update animations
   */
  animationStack * animStackPtr = mainView->animStack;
  if (animStackPtr != NULL) {
    imageChanged = true;

    /** Start the animation stack if it is not started */
    if (!animStackPtr->hasStarted) {
      animStackPtr->start(animStackPtr, mainView->sndStore.rumbling);
    }

    /** Update the animation */
    animStackPtr->update(animStackPtr, mainView->rubikCube);

    /** Remove it if finished */
    if (animStackPtr->isFinished) {
      removeAnimationStack(&mainView->animStack, animStackPtr);
    }
  }

  /** Show the help window if we previously entered the konami code */
  if (mainView->windowToDisplay) {
    showHelpWindow(mainView);
    imageChanged = true;
  }

  SDL_Event event;
  const Uint8 *keystate = SDL_GetKeyboardState(NULL);

  /*
   * Attribute a score depending on key press, will be used later for
   * simple parsing
   * 0: no key combination
   * 1: left control
   * 2: left shift
   * 3: left control + left shift
   */
  int keyShortcut = 0;
  keyShortcut += keystate[SDL_SCANCODE_LSHIFT] ? 2 : 0;
  keyShortcut += keystate[SDL_SCANCODE_LCTRL] ? 1 : 0;

  while (SDL_PollEvent(&event)) {
    switch(event.type)
    {
      case SDL_MOUSEMOTION:
        if (event.type == SDL_MOUSEMOTION && event.motion.state == SDL_BUTTON_LMASK) {
          float zAngle = event.motion.yrel * 0.01;
          float yAngle = event.motion.xrel * 0.01;
          mainCamera->rotate(mainCamera, zAngle, yAngle);
          imageChanged = true;
        }
        break;
      case SDL_MOUSEWHEEL:
        mainCamera->zoom(mainCamera, event.wheel.y > 0);
        imageChanged = true;
        break;
      case SDL_QUIT:
        closeWindow();
        break;
      case SDL_WINDOWEVENT:
        if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
          if (event.window.windowID == SDL_GetWindowID(mainView->mainWindow)) {
            closeWindow();
          }
          else {
            SDL_DestroyWindow(mainView->solveWindow);
            mainView->windowDisplayed = false;
          }
        }
        break;
    }

    bool keyPressed = event.key.type == SDL_KEYDOWN && event.key.repeat == 0;

    if (keyPressed) {
      int * konamiCount = &mainView->konamiCount;

      /** Konami code state machine. Wow ! Two lines only, for real */
      // if (event.key.keysym.sym == konamiCode[*konamiCount]) (*konamiCount)++;
      // else *konamiCount = 0;
      /** Okay, this one is one line */
      *konamiCount += event.key.keysym.sym == konamiCode[*konamiCount] ? 1 : -*konamiCount;

      /** Make a solution request if konami code has been typed */
      if (*konamiCount == 10) {
        enqueue(moveQueue, SOLVE_PLS);
        mainView->windowToDisplay = true;
        *konamiCount = 0;
        imageChanged = true;
      }
    }

    /** Press I to show the instructions overlay */
    if (event.key.keysym.sym == SDLK_i && keyPressed) {
      mainView->instructionsDisplayed = !mainView->instructionsDisplayed;
      imageChanged = true;
    }

    /** Press escape to quit */
    if (event.key.keysym.sym == SDLK_ESCAPE && keyPressed) {
      closeWindow();
    }

    /** FOR DEBUGGING PURPOSE ONLY : Win/unwin the game */
    if (event.key.keysym.sym == SDLK_F10 && keyPressed) {
      mainView->gameWon = !mainView->gameWon;
      if (mainView->gameWon) {
        playWinningSequence(mainView);
      }
      imageChanged = true;
    }

    /** Press F2 to start a new game */
    if(event.key.keysym.sym == SDLK_F2 && keyPressed) {
      enqueue(moveQueue, RESTART);
    }

    /*
     * Check if the game is won. If it is, we won't continue checking the
     * inputs : we don't want the player to still be able to make moves
     */
    if (mainView->gameWon) {
      continue;
    }

    /** Make a move request in case a key has been pressed */
    if (keyPressed) {
      move newMove = getNextMove(event.key.keysym.sym, keyShortcut);
      if (newMove != (move)-1) {
        enqueue(moveQueue, newMove);
      }
    }
  }

  /******************
   * Draw the scene *
   ******************/

  if (!imageChanged) {
    Uint32 endTime = SDL_GetTicks() - startTime;
    if (endTime < 16){
      SDL_Delay(16 - endTime);
    }
  }

  /** Clear the screen */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /*
   * Set the matrix mode to the model view. The next operations will be applied
   * on the matrix containing all the vertices and stuff like that
   */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  /** Set the camera position and orientation */
  gluLookAt(mainCamera->position.x, mainCamera->position.y, mainCamera->position.z, 0, 0, 0, 0, 0, 1);

  /** Draw the skybox before anything */
  drawSkybox(mainView->texStore.skybox);

  /** Set the lightings parameters */
  GLfloat light_diffuse[] = {1, 1, 1, 1};
  GLfloat light_specular[] = {0.9, 0.9, 0.9, 1};

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, light_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, light_specular);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glMateriali(GL_FRONT, GL_SHININESS, 96);
  glEnable(GL_COLOR_MATERIAL);

  /** Draw the 3D stuffs */
  drawCubes(mainView->rubikCube);
  if (mainView->instructionsDisplayed) {
    drawInstructions(mainView->instructions, keyShortcut);
  }

  /*
   * Set the scene for some 2D:
   * Disabling lighting and depth testing
   */
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glDepthMask(GL_FALSE);

  /*
   * We will temporarily add an orthometric matrix to the projection
   * matrix so that we can draw in 2D. We will pop it back later when we go
   * back to 3D.
   */
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0.0, 800, 0.0, 600);

  /*
   * We push a new model view matrix on top of the existing one to make the
   * 2D on top of the 3D.
   */
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  /** Start drawing in 2D */
  glEnable(GL_TEXTURE_2D);

  /** Draw history, xyz instruction and the winning creepy guy if needed */
  drawHistory(mainView->texStore, moveStack);
  drawXYZInstruction(mainView->texStore, keystate[SDL_SCANCODE_LSHIFT]);
  if (mainView->gameWon) {
    drawWinning(mainView->texStore);
  }

  /** Stop drawin in 3D */
  glDisable(GL_TEXTURE_2D);

  /** We pop the projection and modelview matrices we used in 2D */
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  /** We reenable the lights and depth testing for 3D */
  glDepthMask(GL_TRUE);
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);

  /** Displaying final screen */
  glFlush();
  SDL_GL_SwapWindow(mainView->mainWindow);


  /*
   * Update the solve window
   */
  if (mainView->windowDisplayed) {
    SDL_Surface * solveSurface = SDL_GetWindowSurface(mainView->solveWindow);
    SDL_FillRect(solveSurface, NULL, SDL_MapRGB(solveSurface->format, 0, 0, 0));
    move * moves = head(solveMoves, 13);
    //move * moves = solveMoves;
    for (int i = 0; i < 13 && (int)moves[i] != -1; i++) {
      SDL_Rect position;
      position.x = 20 + 70 * i;
      position.y = 20;
      position.h = 50;
      position.w = 50;

      SDL_BlitScaled(moveToTexture(mainView->texStore, moves[i]).surface, NULL, solveSurface, &position);
    }

    SDL_UpdateWindowSurface(mainView->solveWindow);
  }

  Uint32 endTime = SDL_GetTicks() - startTime;
  if (endTime < 16){
    SDL_Delay(16 - endTime);
  }
}


/******************************************************************************
 * CAMERA CONTROLS
 ******************************************************************************/


void rotateCamera(camera * self, float zAngle, float yAngle) {
  self->angles.y -= yAngle;
  self->angles.z -= zAngle;

  /** Limit the z angle so we don't get upside down */
  if (self->angles.z < 0) {
    self->angles.z = 0.000001;
  } else if (self->angles.z > PI) {
    self->angles.z = PI - 0.000001;
  }

  self->position = polarToCartesian(self->angles);
}


void zoomCamera(camera * self, bool positive) {
  if (positive) {
    self->angles.x -= 0.1;

    /** Limit the near distance to 4 */
    if (self->angles.x < 4) {
      self->angles.x = 4;
    }
  } else {
    self->angles.x += 0.1;

    /** Limit the far distance to 50 */
    if (self->angles.x > 50) {
      self->angles.x = 50;
    }
  }

  self->position = polarToCartesian(self->angles);
}


vector3 polarToCartesian(vector3 polar) {
  vector3 cartesian;
  cartesian.x = polar.x * sinf(polar.z) * cosf(polar.y);
  cartesian.y = polar.x * sinf(polar.z) * sinf(polar.y);
  cartesian.z = polar.x * cosf(polar.z);
  return cartesian;
}


/******************************************************************************
 * ROTATING FACES DATA
 *
 * Here we rotate the matrices 90° or -90°. The techniques as are follow:
 *
 * Rotating 90°:
 * 1. Transpose
 * 2. Reverse each row
 *
 * Rotating -90°:
 * 1. Transpose
 * 2. Reverse each column
 ******************************************************************************/


void rotateDataX(rubikcube * rubikCube, int xIndex, bool ccw) {
  /**
   * Transposing the matrix
   */
  for (int yIndex = 1; yIndex < 3; yIndex++) {
    for (int zIndex = 0; zIndex < yIndex; zIndex++) {
      cube3d * tempCube = rubikCube->cubes[xIndex][yIndex][zIndex];
      rubikCube->cubes[xIndex][yIndex][zIndex] = rubikCube->cubes[xIndex][zIndex][yIndex];
      rubikCube->cubes[xIndex][zIndex][yIndex] = tempCube;
    }
  }

  if (ccw) {
    /*
     * Exchanging the columns
     */
    for (int yIndex = 0; yIndex < 3; yIndex++) {
      cube3d * tempCube = rubikCube->cubes[xIndex][yIndex][0];
      rubikCube->cubes[xIndex][yIndex][0] = rubikCube->cubes[xIndex][yIndex][2];
      rubikCube->cubes[xIndex][yIndex][2] = tempCube;
    }
  } else {
    /*
     * Exchanging the rows
     */
    for (int zIndex = 0; zIndex < 3; zIndex++) {
      cube3d * tempCube = rubikCube->cubes[xIndex][0][zIndex];
      rubikCube->cubes[xIndex][0][zIndex] = rubikCube->cubes[xIndex][2][zIndex];
      rubikCube->cubes[xIndex][2][zIndex] = tempCube;
    }
  }
}


void rotateDataY(rubikcube * rubikCube, int yIndex, bool ccw) {
  /**
   * Transposing the matrix
   */
  for (int xIndex = 1; xIndex < 3; xIndex++) {
    for (int zIndex = 0; zIndex < xIndex; zIndex++) {
      cube3d * tempCube = rubikCube->cubes[xIndex][yIndex][zIndex];
      rubikCube->cubes[xIndex][yIndex][zIndex] = rubikCube->cubes[zIndex][yIndex][xIndex];
      rubikCube->cubes[zIndex][yIndex][xIndex] = tempCube;
    }
  }

  if (ccw) {
    /*
     * Exchanging the columns
     */
    for (int zIndex = 0; zIndex < 3; zIndex++) {
      cube3d * tempCube = rubikCube->cubes[0][yIndex][zIndex];
      rubikCube->cubes[0][yIndex][zIndex] = rubikCube->cubes[2][yIndex][zIndex];
      rubikCube->cubes[2][yIndex][zIndex] = tempCube;
    }
  } else {
    /*
     * Exchanging the rows
     */
    for (int xIndex = 0; xIndex < 3; xIndex++) {
      cube3d * tempCube = rubikCube->cubes[xIndex][yIndex][0];
      rubikCube->cubes[xIndex][yIndex][0] = rubikCube->cubes[xIndex][yIndex][2];
      rubikCube->cubes[xIndex][yIndex][2] = tempCube;
    }
  }
}


void rotateDataZ(rubikcube * rubikCube, int zIndex, bool ccw) {
  /**
   * Transposing the matrix
   */
  for (int xIndex = 1; xIndex < 3; xIndex++) {
    for (int yIndex = 0; yIndex < xIndex; yIndex++) {
      cube3d * tempCube = rubikCube->cubes[xIndex][yIndex][zIndex];
      rubikCube->cubes[xIndex][yIndex][zIndex] = rubikCube->cubes[yIndex][xIndex][zIndex];
      rubikCube->cubes[yIndex][xIndex][zIndex] = tempCube;
    }
  }

  if (!ccw) {
    /*
     * Exchanging the rows
     */
    for (int yIndex = 0; yIndex < 3; yIndex++) {
      cube3d * tempCube = rubikCube->cubes[0][yIndex][zIndex];
      rubikCube->cubes[0][yIndex][zIndex] = rubikCube->cubes[2][yIndex][zIndex];
      rubikCube->cubes[2][yIndex][zIndex] = tempCube;
    }
  } else {
    /*
     * Exchanging the columns
     */
    for (int xIndex = 0; xIndex < 3; xIndex++) {
      cube3d * tempCube = rubikCube->cubes[xIndex][0][zIndex];
      rubikCube->cubes[xIndex][0][zIndex] = rubikCube->cubes[xIndex][2][zIndex];
      rubikCube->cubes[xIndex][2][zIndex] = tempCube;
    }
  }
}


/******************************************************************************
 * ORDERS AND MOVES
 ******************************************************************************/


move getNextMove(SDL_Keycode keysym, int keyShortcut) {
  move nextMove = (move)-1;

  // DOWN ROTATION
  if (keysym == SDLK_d) {
    move moves[] = {D, d, Di, di};
    nextMove = moves[keyShortcut];
  }

  // UP ROTATION
  if (keysym == SDLK_u) {
    move moves[] = {U, u, Ui, ui};
    nextMove = moves[keyShortcut];
  }

  // RIGHT ROTATION
  if (keysym == SDLK_r) {
    move moves[] = {R, r, Ri, ri};
    nextMove = moves[keyShortcut];
  }

  // LEFT ROTATION
  if (keysym == SDLK_l) {
    move moves[] = {L, l, Li, li};
    nextMove = moves[keyShortcut];
  }

  // FRONT ROTATION
  if (keysym == SDLK_f) {
    move moves[] = {F, f, Fi, fi};
    nextMove = moves[keyShortcut];
  }

  // BACK ROTATION
  if (keysym == SDLK_b) {
    move moves[] = {B, b, Bi, bi};
    nextMove = moves[keyShortcut];
  }

  // X ROTATION
  if (keysym == SDLK_x) {
    nextMove = keyShortcut >= 2 ? xi : x;
  }

  // Y ROTATION
  if (keysym == SDLK_y) {
    nextMove = keyShortcut >= 2 ? yi : y;
  }

  // Z ROTATION
  if (keysym == SDLK_z) {
    nextMove = keyShortcut >= 2 ? zi : z;
  }

  if(keysym == SDLK_BACKSPACE) {
    nextMove = RETURN;
  }

  return nextMove;
}


void parseOrder(rubikview * mainView, move order, bool fast) {
  animation * newAnimation;
  animationStack * newAnimStack = generateAnimationStack(mainView->sndStore.rumbling);
  float rotationAngle = fast ? PI / 2 : ROTATION_ANGLE;
  switch (order) {
    case U:
      newAnimation = generateAnimation(TOP, 2, rotationAngle, true, &rotateDataZ);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case D:
      newAnimation = generateAnimation(DOWN, 0, rotationAngle, false, &rotateDataZ);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case R:
      newAnimation = generateAnimation(RIGHT, 2, rotationAngle, true, &rotateDataX);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case L:
      newAnimation = generateAnimation(LEFT, 0, rotationAngle, false, &rotateDataX);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case F:
      newAnimation = generateAnimation(FRONT, 0, rotationAngle, false, &rotateDataY);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case B:
      newAnimation = generateAnimation(BACK, 2, rotationAngle, true, &rotateDataY);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;

    case Ui:
      newAnimation = generateAnimation(TOP, 2, rotationAngle, false, &rotateDataZ);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case Di:
      newAnimation = generateAnimation(DOWN, 0, rotationAngle, true, &rotateDataZ);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case Ri:
      newAnimation = generateAnimation(RIGHT, 2, rotationAngle, false, &rotateDataX);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case Li:
      newAnimation = generateAnimation(LEFT, 0, rotationAngle, true, &rotateDataX);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case Fi:
      newAnimation = generateAnimation(FRONT, 0, rotationAngle, true, &rotateDataY);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case Bi:
      newAnimation = generateAnimation(BACK, 2, rotationAngle, false, &rotateDataY);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;

    case u:
      newAnimation = generateAnimation(TOP, 2, rotationAngle, true, &rotateDataZ);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(TOP, 1, rotationAngle, true, &rotateDataZ);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case d:
      newAnimation = generateAnimation(DOWN, 0, rotationAngle, false, &rotateDataZ);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(DOWN, 1, rotationAngle, false, &rotateDataZ);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case r:
      newAnimation = generateAnimation(RIGHT, 2, rotationAngle, true, &rotateDataX);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(RIGHT, 1, rotationAngle, true, &rotateDataX);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case l:
      newAnimation = generateAnimation(LEFT, 0, rotationAngle, false, &rotateDataX);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(LEFT, 1, rotationAngle, false, &rotateDataX);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case f:
      newAnimation = generateAnimation(FRONT, 0, rotationAngle, false, &rotateDataY);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(FRONT, 1, rotationAngle, false, &rotateDataY);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case b:
      newAnimation = generateAnimation(BACK, 2, rotationAngle, true, &rotateDataY);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(BACK, 1, rotationAngle, true, &rotateDataY);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;

    case ui:
      newAnimation = generateAnimation(TOP, 2, rotationAngle, false, rotateDataZ);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(TOP, 1, rotationAngle, false, rotateDataZ);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case di:
      newAnimation = generateAnimation(DOWN, 0, rotationAngle, true, rotateDataZ);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(DOWN, 1, rotationAngle, true, rotateDataZ);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case ri:
      newAnimation = generateAnimation(RIGHT, 2, rotationAngle, false, rotateDataX);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(RIGHT, 1, rotationAngle, false, rotateDataX);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case li:
      newAnimation = generateAnimation(LEFT, 0, rotationAngle, true, rotateDataX);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(LEFT, 1, rotationAngle, true, rotateDataX);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case fi:
      newAnimation = generateAnimation(FRONT, 0, rotationAngle, true, &rotateDataY);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(FRONT, 1, rotationAngle, true, &rotateDataY);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case bi:
      newAnimation = generateAnimation(BACK, 2, rotationAngle, false, &rotateDataY);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(BACK, 1, rotationAngle, false, &rotateDataY);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;

    case x:
      newAnimation = generateAnimation(RIGHT, 0, rotationAngle, true, &rotateDataX);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(RIGHT, 2, rotationAngle, true, &rotateDataX);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(RIGHT, 1, rotationAngle, true, &rotateDataX);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case xi:
      newAnimation = generateAnimation(RIGHT, 0, rotationAngle, false, &rotateDataX);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(RIGHT, 2, rotationAngle, false, &rotateDataX);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(RIGHT, 1, rotationAngle, false, &rotateDataX);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;

    case y:
      newAnimation = generateAnimation(TOP, 0, rotationAngle, true, &rotateDataZ);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(TOP, 2, rotationAngle, true, &rotateDataZ);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(TOP, 1, rotationAngle, true, &rotateDataZ);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case yi:
      newAnimation = generateAnimation(TOP, 0, rotationAngle, false, &rotateDataZ);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(TOP, 2, rotationAngle, false, &rotateDataZ);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(TOP, 1, rotationAngle, false, &rotateDataZ);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;

    case z:
      newAnimation = generateAnimation(FRONT, 0, rotationAngle, false, &rotateDataY);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(FRONT, 2, rotationAngle, false, &rotateDataY);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(FRONT, 1, rotationAngle, false, &rotateDataY);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case zi:
      newAnimation = generateAnimation(FRONT, 0, rotationAngle, true, &rotateDataY);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(FRONT, 2, rotationAngle, true, &rotateDataY);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(FRONT, 1, rotationAngle, true, &rotateDataY);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;

    default:
      break;
  }
  addAnimationStack(&mainView->animStack, newAnimStack);
}


soundStore generateSoundStore() {
  soundStore sndStore;
  sndStore.rumbling = Mix_LoadWAV("res/sounds/rumble.wav");
  sndStore.clapping = Mix_LoadWAV("res/sounds/clapping.wav");
  return sndStore;
}


void resetView(rubikview * aView) {
    // Reset camera
    aView->mainCamera = generateCamera();

    // Empty the animation stack just to be safe
    aView->animStack = NULL;

    // Frees the rubikCube
    // Overkill, just to show off that we planned to free the allocated mem
    destroyRubikCube(aView->rubikCube);
    aView->rubikCube = generateRubikCube();
    aView->gameWon = false;
    aView->instructionsDisplayed = false;
    aView->konamiCount = 0;
    return;
}


void playWinningSequence(rubikview * mainView) {
  mainView->gameWon = true;
  Mix_PlayChannel(1, mainView->sndStore.clapping, 0);
}


void closeWindow() {
  SDL_Quit();
  exit(0);
}
