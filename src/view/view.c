/**
 * @file view.c
 */


#include "view.h"


static SDL_Window *screen;
static SDL_Window *solveScreen;
static SDL_GLContext mainContext;
//static SDL_Surface * img;
static bool windowToDisplay = false;
static bool windowDisplayed = false;
SDL_Surface * solveSurface = NULL;
TTF_Font * police = NULL;

void setWindow() {
  /*
   * Initialize SDL
   */
  SDL_Init(SDL_INIT_VIDEO);

  //img = IMG_Load("res/xyz.png");

  /*
   * Bind the SDL_Quit() function to the program's exit
   */
  atexit(SDL_Quit);

  /*
   * Enabling SDL multisampling (antialiasing)
   */
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

  /*
   *  Set the window title and set the window size, the colour depth and
   *  context to OpenGL
   */
  //SDL_WM_SetCaption("Rubiksawesome", NULL);
  //SDL_SetVideoMode(800, 600, 32, SDL_OPENGL);
  screen = SDL_CreateWindow("Rubiksawesome",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          800, 600,
                          SDL_WINDOW_OPENGL);
  SDL_CreateRenderer(screen, -1, 0);
  mainContext = SDL_GL_CreateContext(screen);

  SDL_GL_MakeCurrent(screen, mainContext);

  /*
   * Set up of the projection matrix to use perspective
   */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, (double)800 / 600, 1, 1000);

  /*
   * Enable depth testing (allows objects to hide each others)
   */
  glEnable(GL_DEPTH_TEST);

  /*
   * Enable transparency by enabling blending between alpha channel and
   * previous alpha channel
   */
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  /*
   * Enable lighting
   */
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  /*
   * Enable OpenGL multisampling (antialiasing)
   */
  glEnable(GL_MULTISAMPLE);

  /*
   * Create light components and assign them to GL_LIGHT0
   */
  GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
  GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
  GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
  GLfloat position[] = { -1.0f, 0, 0, 1.0f };

  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
  glLightfv(GL_LIGHT0, GL_POSITION, position);

  /*
   * Initialize sound
   */
  if (Mix_OpenAudio(24000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
    printf("%s", Mix_GetError());
  }
  Mix_AllocateChannels(2);

  /*
   * Initialize TTF
   */
  TTF_Init();
  police = TTF_OpenFont("res/MontserratAlternates-Regular.ttf", 48);
  if(!police) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    // handle error
  }

  /*
   * Display SDL and OpenGL versions
   */
  SDL_version sdlVersion;
  SDL_VERSION(&sdlVersion);
  printf("SDL version: %d.%d.%d\n", sdlVersion.major, sdlVersion.minor, sdlVersion.patch);
  printf("OpenGL version: %s\n", glGetString(GL_VERSION));
  fflush(stdout);
}


rubikview generateView() {
  /*
   * Set the camera starting position
   */
  camera mainCamera = {
    (vector3) {0, 0, 0},
    (vector3) {8, - 3 * PI / 4, PI / 3}
  };

  /*
   * Create the cube and assign the camera, the rubik's cube and an empty
   * animations list
   */
  rubikview mainView;
  mainView.texStore = generateTextureStore();
  mainView.sndStore = generateSoundStore();

  memcpy(&(mainView.mainCamera), &mainCamera, sizeof(camera));
  mainView.rubikCube = generateRubikCube();
  mainView.animStack = NULL;
  mainView.gameWon = false;
  mainView.konamiCount = 0;

  /*
   * Generates instructions and add them to the view (hidden by default)
   */
  enum FaceType facesTypes[6] = {FRONT, RIGHT, TOP, DOWN, BACK, LEFT};
  for (int instructionIndex = 0; instructionIndex < 6; instructionIndex++) {
    mainView.instructions[instructionIndex] = generateInstruction(facesTypes[instructionIndex], mainView.texStore);
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


void update(rubikview * mainView, mvqueue moveQueue, mvstack moveStack) {
  camera * mainCamera = &(mainView->mainCamera);

  /*
   * Update animations
   */
  animationStack * animStackPtr = mainView->animStack;
  if (animStackPtr != NULL) {
    if (!animStackPtr->hasStarted) {
      Mix_PlayChannel(0, mainView->sndStore.rumbling, 0);
      animStackPtr->hasStarted = true;
    }
    animation * animationsPtr = animStackPtr->animations;
    bool stackFinished = false;
    while (animationsPtr != NULL) {
      animationsPtr->update(animationsPtr, mainView->rubikCube);
      stackFinished = animationsPtr->isActive;
      animationsPtr = animationsPtr->next;
    }
    if (!stackFinished) {
      removeAnimationStack(&mainView->animStack, animStackPtr);
    }
  }

  if (windowToDisplay) {
    windowToDisplay = false;
    SDL_DestroyWindow(solveScreen);
    windowDisplayed = false;
    solveScreen = SDL_CreateWindow("Help",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            300, 100, 0);
    windowDisplayed = true;
    solveSurface = SDL_GetWindowSurface(solveScreen);
  }

  SDL_Event event;
  const Uint8 *keystate = SDL_GetKeyboardState(NULL);

  while (SDL_PollEvent(&event)) {
    switch(event.type)
    {
      case SDL_MOUSEMOTION:
        if (event.type == SDL_MOUSEMOTION && event.motion.state == SDL_BUTTON_LMASK) {
          mainCamera->angles.y -= event.motion.xrel * 0.01;
          mainCamera->angles.z -= event.motion.yrel * 0.01;

          if (mainCamera->angles.z < 0) {
            mainCamera->angles.z = 0.000001;
          } else if (mainCamera->angles.z > PI) {
            mainCamera->angles.z = PI - 0.000001;
          }
        }
        break;
      case SDL_MOUSEWHEEL:
        if (event.wheel.y > 0) {
          mainCamera->angles.x -= 0.1;
          if (mainCamera->angles.x < 4) {
            mainCamera->angles.x = 4;
          }
        }

        if (event.wheel.y < 0) {
          mainCamera->angles.x += 0.1;
          if (mainCamera->angles.x > 50) {
            mainCamera->angles.x = 50;
          }
        }
        break;
      case SDL_QUIT:
        exit(0);
        break;
      case SDL_WINDOWEVENT:
        if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
          if (event.window.windowID == SDL_GetWindowID(screen)) {
            exit(0);
          }
          else {
            SDL_DestroyWindow(solveScreen);
            windowDisplayed = false;
          }
        }
        break;
    }

    int evntSym = event.key.keysym.sym;
    int * konamiCount = &mainView->konamiCount;
    if (event.key.type == SDL_KEYDOWN) {
      if (*konamiCount == 0 && evntSym == SDLK_UP) { (*konamiCount)++; }
      else if (*konamiCount == 1 && evntSym == SDLK_UP) { (*konamiCount)++; }
      else if (*konamiCount == 2 && evntSym == SDLK_DOWN) { (*konamiCount)++; }
      else if (*konamiCount == 3 && evntSym == SDLK_DOWN) { (*konamiCount)++; }
      else if (*konamiCount == 4 && evntSym == SDLK_LEFT) { (*konamiCount)++; }
      else if (*konamiCount == 5 && evntSym == SDLK_RIGHT) { (*konamiCount)++; }
      else if (*konamiCount == 6 && evntSym == SDLK_LEFT) { (*konamiCount)++; }
      else if (*konamiCount == 7 && evntSym == SDLK_RIGHT) { (*konamiCount)++; }
      else if (*konamiCount == 8 && evntSym == SDLK_b) { (*konamiCount)++; }
      else if (*konamiCount == 9 && evntSym == SDLK_a) {
        printf("KONAMI CODE!\n");
        enqueue(moveQueue, SOLVE_PLS);
        windowToDisplay = true;
        *konamiCount = 0;
      }
      else {
        *konamiCount = 0;
      }
    }

    if (event.key.keysym.sym == SDLK_i && event.key.type == SDL_KEYDOWN) {
      mainView->instructionsDisplayed = !mainView->instructionsDisplayed;
    }

    if (event.key.keysym.sym == SDLK_ESCAPE && event.key.type == SDL_KEYDOWN) {
      exit(0);
    }

    if (event.key.keysym.sym == SDLK_F10 && event.key.type == SDL_KEYDOWN) {
      mainView->gameWon = !mainView->gameWon;
      if (mainView->gameWon) {
        Mix_PlayChannel(1, mainView->sndStore.clapping, 0);
      }
    }

    if(event.key.keysym.sym == SDLK_F2 \
            && event.key.type == SDL_KEYDOWN) {
      enqueue(moveQueue, RESTART);
    }

    if (mainView->gameWon) {
      continue;
    }

    move newMove;

    // DOWN ROTATION
    if (event.key.keysym.sym == SDLK_d && event.key.type == SDL_KEYDOWN) {
      if (keystate[SDL_SCANCODE_LSHIFT] && keystate[SDL_SCANCODE_LCTRL]) {
        newMove = di;
      } else if (keystate[SDL_SCANCODE_LSHIFT] && !keystate[SDL_SCANCODE_LCTRL]) {
        newMove = Di;
      } else if (!keystate[SDL_SCANCODE_LSHIFT] && keystate[SDL_SCANCODE_LCTRL]) {
        newMove = d;
      } else {
        newMove = D;
      }

      enqueue(moveQueue, newMove);
    }

    // UP ROTATION
    if (event.key.keysym.sym == SDLK_u && event.key.type == SDL_KEYDOWN) {
      if (keystate[SDL_SCANCODE_LSHIFT] && keystate[SDL_SCANCODE_LCTRL]) {
        newMove = ui;
      } else if (keystate[SDL_SCANCODE_LSHIFT] && !keystate[SDL_SCANCODE_LCTRL]) {
        newMove = Ui;
      } else if (!keystate[SDL_SCANCODE_LSHIFT] && keystate[SDL_SCANCODE_LCTRL]) {
        newMove = u;
      } else {
        newMove = U;
      }

      enqueue(moveQueue, newMove);
    }

    // RIGHT ROTATION
    if (event.key.keysym.sym == SDLK_r && event.key.type == SDL_KEYDOWN) {
      if (keystate[SDL_SCANCODE_LSHIFT] && keystate[SDL_SCANCODE_LCTRL]) {
        newMove = ri;
      } else if (keystate[SDL_SCANCODE_LSHIFT] && !keystate[SDL_SCANCODE_LCTRL]) {
        newMove = Ri;
      } else if (!keystate[SDL_SCANCODE_LSHIFT] && keystate[SDL_SCANCODE_LCTRL]) {
        newMove = r;
      } else {
        newMove = R;
      }

      enqueue(moveQueue, newMove);
    }

    // LEFT ROTATION
    if (event.key.keysym.sym == SDLK_l && event.key.type == SDL_KEYDOWN) {
      if (keystate[SDL_SCANCODE_LSHIFT] && keystate[SDL_SCANCODE_LCTRL]) {
        newMove = li;
      } else if (keystate[SDL_SCANCODE_LSHIFT] && !keystate[SDL_SCANCODE_LCTRL]) {
        newMove = Li;
      } else if (!keystate[SDL_SCANCODE_LSHIFT] && keystate[SDL_SCANCODE_LCTRL]) {
        newMove = l;
      } else {
        newMove = L;
      }

      enqueue(moveQueue, newMove);
    }

    // FRONT ROTATION
    if (event.key.keysym.sym == SDLK_f && event.key.type == SDL_KEYDOWN) {
      if (keystate[SDL_SCANCODE_LSHIFT] && keystate[SDL_SCANCODE_LCTRL]) {
        newMove = fi;
      } else if (keystate[SDL_SCANCODE_LSHIFT] && !keystate[SDL_SCANCODE_LCTRL]) {
        newMove = Fi;
      } else if (!keystate[SDL_SCANCODE_LSHIFT] && keystate[SDL_SCANCODE_LCTRL]) {
        newMove = f;
      } else {
        newMove = F;
      }

      enqueue(moveQueue, newMove);
    }

    // BACK ROTATION
    if (event.key.keysym.sym == SDLK_b && event.key.type == SDL_KEYDOWN) {
      if (keystate[SDL_SCANCODE_LSHIFT] && keystate[SDL_SCANCODE_LCTRL]) {
        newMove = bi;
      } else if (keystate[SDL_SCANCODE_LSHIFT] && !keystate[SDL_SCANCODE_LCTRL]) {
        newMove = Bi;
      } else if (!keystate[SDL_SCANCODE_LSHIFT] && keystate[SDL_SCANCODE_LCTRL]) {
        newMove = b;
      } else {
        newMove = B;
      }

      enqueue(moveQueue, newMove);
    }

    // X ROTATION
    if (event.key.keysym.sym == SDLK_x && event.key.type == SDL_KEYDOWN) {
      if (keystate[SDL_SCANCODE_LSHIFT]) {
        newMove = xi;
      } else {
        newMove = x;
      }

      enqueue(moveQueue, newMove);
    }

    // Y ROTATION
    if (event.key.keysym.sym == SDLK_y && event.key.type == SDL_KEYDOWN) {
      if (keystate[SDL_SCANCODE_LSHIFT]) {
        newMove = yi;
      } else {
        newMove = y;
      }

      enqueue(moveQueue, newMove);
    }

    // Z ROTATION
    if (event.key.keysym.sym == SDLK_z && event.key.type == SDL_KEYDOWN) {
      if (keystate[SDL_SCANCODE_LSHIFT]) {
        newMove = zi;
      } else {
        newMove = z;
      }

      enqueue(moveQueue, newMove);
    }

    if(event.key.keysym.sym == SDLK_BACKSPACE \
            && event.key.type == SDL_KEYDOWN) {
      newMove = RETURN;
      enqueue(moveQueue, newMove);
    }
  }

  /****************
   *
   * Draw the scene
   *
   ****************/

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity( );

  mainCamera->position.x = mainCamera->angles.x * sinf(mainCamera->angles.z) * cosf(mainCamera->angles.y);
  mainCamera->position.y = mainCamera->angles.x * sinf(mainCamera->angles.z) * sinf(mainCamera->angles.y);
  mainCamera->position.z = mainCamera->angles.x * cosf(mainCamera->angles.z);

  gluLookAt(mainCamera->position.x, mainCamera->position.y, mainCamera->position.z, 0, 0, 0, 0, 0, 1);

  drawSkybox(mainView->texStore.skybox);

  GLfloat light_diffuse[] = {1, 1, 1, 1};
  GLfloat light_specular[] = {0.9, 0.9, 0.9, 1};

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, light_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, light_specular);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glMateriali(GL_FRONT, GL_SHININESS, 96);
  glEnable(GL_COLOR_MATERIAL);

  for (int zIndex = 0; zIndex < 3; zIndex++) {
    for (int yIndex = 0; yIndex < 3; yIndex++) {
      for (int xIndex = 0; xIndex < 3; xIndex++) {
        drawCube(*mainView->rubikCube->cubes[xIndex][yIndex][zIndex], false);
      }
    }
  }

  if (mainView->instructionsDisplayed) {
    for (int instructionIndex = 0; instructionIndex < 6; instructionIndex++) {
      drawInstruction(mainView->instructions[instructionIndex], keystate[SDL_SCANCODE_LSHIFT], keystate[SDL_SCANCODE_LCTRL]);
    }
  }

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glDepthMask(GL_FALSE);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  gluOrtho2D(0.0, 800, 0.0, 600);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  glEnable(GL_TEXTURE_2D);

  /*
   * History display
   */
  move * moves = head(moveStack, 13);
  for (int i = 0; i < 13 && (int)moves[i] != -1; i++) {
    int t = 50;
    int xOffset = i * 60 + 20;
    int yOffset = 20;
    int alpha = 255 - (i * (255 / 13));
    glColor4ub(255, 255, 255, alpha);
    glBindTexture(GL_TEXTURE_2D, moveToTexture(mainView->texStore, moves[i]));
    glBegin(GL_QUADS);
    glTexCoord2i(0,1); glVertex2i(xOffset, yOffset);
    glTexCoord2i(0,0); glVertex2i(xOffset, yOffset + t);
    glTexCoord2i(1,0); glVertex2i(xOffset + t, yOffset + t);
    glTexCoord2i(1,1); glVertex2i(xOffset + t, yOffset);
    glEnd();
  }

  free(moves);

  /*
   * Display xyz instructions
   */
  if (keystate[SDL_SCANCODE_LSHIFT]) {
    glBindTexture(GL_TEXTURE_2D, mainView->texStore.xyzi);
  }
  else {
    glBindTexture(GL_TEXTURE_2D, mainView->texStore.xyz);
  }
  glColor3ub(255, 255, 255);
  glBegin(GL_QUADS);
  glTexCoord2i(0,0); glVertex2i(20, 590);
  glTexCoord2i(0,1); glVertex2i(20, 490);
  glTexCoord2i(1,1); glVertex2i(120, 490);
  glTexCoord2i(1,0); glVertex2i(120, 590);
  glEnd();

  /*
   * Winning texture
   */
  if (mainView->gameWon) {
    glBindTexture(GL_TEXTURE_2D, mainView->texStore.winner);
    glColor4ub(255, 255, 255, 255);
    glBegin(GL_QUADS);
    glTexCoord2i(0,1); glVertex2i(5, 0);
    glTexCoord2i(0,0); glVertex2i(5, 600);
    glTexCoord2i(1,0); glVertex2i(795, 600);
    glTexCoord2i(1,1); glVertex2i(795, 0);
    glEnd();
  }

  glDisable(GL_TEXTURE_2D);

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  glDepthMask(GL_TRUE);
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);

  glFlush();
  SDL_GL_SwapWindow(screen);


  /*
   * Update the solve window
   */
  if (windowDisplayed) {
    SDL_FillRect(solveSurface, NULL, SDL_MapRGB(solveSurface->format, 0, 0, 0));
    move * moves = head(moveStack, 13);
    for (int i = 0; i < 13 && (int)moves[i] != -1; i++) {
      SDL_Color white = {255, 255, 255, 255};
      SDL_Surface * text = TTF_RenderText_Blended(police, mapMoveToCode(moves[i]), white);
      SDL_Rect position;
      position.x = 10 + (i * 50);
      position.y = 20;
      SDL_BlitSurface(text, NULL, solveSurface, &position);
    }

    free(moves);

    // int height = 100;
    // int width = 100;
    // SDL_Rect texr;
    // texr.x = 100;
    // texr.y = 100;
    // texr.w = width * 2;
    // texr.h = height * 2;
    // SDL_BlitSurface(img, &texr, solveSurface, NULL);
    SDL_UpdateWindowSurface(solveScreen);
  }
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


void parseOrder(rubikview * mainView, move order, bool fast) {
  animation * newAnimation;
  animationStack * newAnimStack = generateAnimationStack(mainView->sndStore.rumbling);
  float rotationAngle = fast ? PI / 2 : ROTATION_ANGLE;
  switch (order) {
    case U:
      newAnimation = generateAnimation(TOP, 2, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case D:
      newAnimation = generateAnimation(DOWN, 0, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case R:
      newAnimation = generateAnimation(RIGHT, 2, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case L:
      newAnimation = generateAnimation(LEFT, 0, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case F:
      newAnimation = generateAnimation(FRONT, 0, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case B:
      newAnimation = generateAnimation(BACK, 2, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;

    case Ui:
      newAnimation = generateAnimation(TOP, 2, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case Di:
      newAnimation = generateAnimation(DOWN, 0, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case Ri:
      newAnimation = generateAnimation(RIGHT, 2, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case Li:
      newAnimation = generateAnimation(LEFT, 0, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case Fi:
      newAnimation = generateAnimation(FRONT, 0, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case Bi:
      newAnimation = generateAnimation(BACK, 2, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;

    case u:
      newAnimation = generateAnimation(TOP, 2, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(TOP, 1, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case d:
      newAnimation = generateAnimation(DOWN, 0, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(DOWN, 1, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case r:
      newAnimation = generateAnimation(RIGHT, 2, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(RIGHT, 1, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case l:
      newAnimation = generateAnimation(LEFT, 0, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(LEFT, 1, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case f:
      newAnimation = generateAnimation(FRONT, 0, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(FRONT, 1, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case b:
      newAnimation = generateAnimation(BACK, 2, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(BACK, 1, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;

    case ui:
      newAnimation = generateAnimation(TOP, 2, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(TOP, 1, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case di:
      newAnimation = generateAnimation(DOWN, 0, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(DOWN, 1, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case ri:
      newAnimation = generateAnimation(RIGHT, 2, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(RIGHT, 1, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case li:
      newAnimation = generateAnimation(LEFT, 0, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(LEFT, 1, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case fi:
      newAnimation = generateAnimation(FRONT, 0, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(FRONT, 1, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case bi:
      newAnimation = generateAnimation(BACK, 2, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(BACK, 1, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;

    case x:
      newAnimation = generateAnimation(RIGHT, 0, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(RIGHT, 2, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(RIGHT, 1, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case xi:
      newAnimation = generateAnimation(RIGHT, 0, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(RIGHT, 2, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(RIGHT, 1, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;

    case y:
      newAnimation = generateAnimation(TOP, 0, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(TOP, 2, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(TOP, 1, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case yi:
      newAnimation = generateAnimation(TOP, 0, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(TOP, 2, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(TOP, 1, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;

    case z:
      newAnimation = generateAnimation(FRONT, 0, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(FRONT, 2, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(FRONT, 1, rotationAngle, false);
      addAnimation(&newAnimStack->animations, newAnimation);
      break;
    case zi:
      newAnimation = generateAnimation(FRONT, 0, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(FRONT, 2, rotationAngle, true);
      addAnimation(&newAnimStack->animations, newAnimation);
      newAnimation = generateAnimation(FRONT, 1, rotationAngle, true);
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


void closeWindow() {
  TTF_CloseFont(police);
  TTF_Quit();
  SDL_Quit();
}
