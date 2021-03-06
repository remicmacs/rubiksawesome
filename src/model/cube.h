#ifndef CUBE_H
#define CUBE_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../controller/errorController.h"

/**
 * Enumeration of all moves implemented by the public method rotate.
 */
typedef enum {
    F,B,R,L,U,D,
    f,b,r,l,u,d,
    x,y,z,           // native moves [0-14]
    Fi,Bi,Ri,Li,Ui,Di, 
    fi,bi,ri,li,ui,di,
    xi,yi,zi,       // complementary moves [15 - 29]
    F2,B2,R2,L2,U2,D2,
    f2,b2,r2,l2,u2,d2,
    x2,y2,z2,
    Fi2,Bi2,Ri2,Li2,Ui2,Di2,
    fi2,bi2,ri2,li2,ui2,di2,
    xi2,yi2,zi2,     // Double moves [30 - 59]
    RETURN, RESTART, SOLVE_PLS
} move;

/**
 * Returns the inverse of the given move
 *
 * If a cube is modified this way :
 * ```C
 *  move aMove = F;
 *  cube aCube = initCube();
 *  aCube->rotate(aMove);
 *  aCube->rotate(inverseMove(aMove));
 *  ```
 *  then the cube shouldn't be modified
 *
 *  @param aMove the move to be inversed
 *  @returns a move being the inverse of aMove
 */
move inverseMove(move aMove);


/**
 * Data structure to hold cube state function handle to manipulate cube.
 */
typedef struct cubeStruct{
    unsigned char ** cube[6];
    struct cubeStruct * (*rotate)(struct cubeStruct *, move);
    struct cubeStruct * (*copy)(struct cubeStruct *);
    _Bool (*equals)(struct cubeStruct *, struct cubeStruct *);
    void (*print)(struct cubeStruct *);
} cube ;

/**
 * Function to map a char * token to a given move.
 *
 * The function maps a valid string token to all the 60 moves implemented.
 * The token format is the following :
 *  <BASEMOVE>[i][2]
 *
 *  BASEMOVE : F|B|R|L|U|D
 *
 *  [i] : counter-clockwise rotation notation
 *  [2] : double rotation
 *
 * @param moveCode the string token of the given move
 *
 * @returns a enum move representing the rotation, -1 if the code is incorrect
 * @see enum move
 */
move mapCodeToMove(char * moveCode);

/**
 * Returns a string matching the given move.
 *
 * The function maps a valid move variable with a string token describing one of
 * all the 60 moves implemented.
 * Useful to print sequences of commands.
 *
 * @param aMove the move variable describing a move command
 * @returns a char * describing by a literal code the corresponding move
 *  e.g. : F2 => "F2"
 */
char * mapMoveToCode(move aMove);

/**
 * Returns the string of commands to perform to reach a specific orientation
 *
 * @param self the cube to position
 * @param frontFace the color of the face to be on front
 * @param upFace the color of the face to be up
 *
 * @returns a string of max two space separated commands
 */
char * positionCommand(cube * self, char frontFace, char upFace);

/**
 * Positions the cube according to two reference faces
 *
 * Calls to this function will use x, y, z rotations to positions cube without
 * modifying it with center of frontFace color on F, center of upFace color on U
 *
 * @param self pointer to the cube to position
 * @param frontFace char id for the color of the center to put on front
 * @param upFace char id for the color of the center to put on up
 * @returns pointer to repositioned cube
 */
cube * positionCube(cube * self, char frontFace, char upFace);

/**
 * Cube initialization to unscrambled Rubik's Cube.
 *
 * Initialize the cube to :
 *  F: Green == 'g'
 *  B: Blue == 'b'
 *  R: Red == 'r'
 *  L: Orange == 'o'
 *  U: White == 'w'
 *  D: Yellow == 'y'
 *  Links public methods to data structures
 *  Initialized cube carries an interface with itself :
 *      ```C
 *          cube * newCube = initCube();
 *          newCube->rotate(newCube,"F"); // rotate cube
 *          // Make a deep copy of the cube
 *          cube * copyCube = newCube->copy(newCube);
 *          // Compares two cubes
 *          _Bool cubesAreEqual = newCube->equals(newCube, copyCube);
 *          newCube->print(newCube); // prints cube to stderr
 *      ```
 *  @returns the initialized cube pointer is returned
 */
cube * initCube();

////////////////////////////////////// PUBLIC METHODS //////////////////////////

/**
 * Main handle to change cube data structure.
 *
 * Rotates the cube given a string token. Tokens may be longer than 3 chars byt
 *  won't be parsed further than moveCode[2], given mapCodeToMove()
 *  implementation.
 *
 *
 * Inputs :
 *   @param self cube to be modified
 *   @param moveCode Code of unique rotation to apply in a string token
 *      Rotations can be :
 *          * Unique or double with a "2" modifier at the end of string
 *          * Clockwise or counter-clockwise with a "i" modifier between the
 *              face code and the double modifier if it exists
 *
 *      Examples of valid rotations:
 *          "R"
 *          "Ri"
 *          "U2"
 *          "Fi2"
 *
 *  Output :
 *  @returns modified cube data structure
 *
 *  @see mapCodeToMove()
 */
cube * rotate(cube * self, move moveCode);

/**
 * Deep copy function to copy a cube.
 *
 * Does a deep copy of the cube pointed to by self. This is a **deep** copy and
 * not a **clone**. Hence, new faces and rows are created and allocated.
 * Therefore modifying the original won't have any influence on the copy and
 * vice-versa.
 * All cubes created with this function should be properly destroyed with
 * destroyCube(cube *)
 *
 *  @param self pointer to cube to be copied
 *  @returns a pointer to the copy of passed cube
 *
 *  @see destroyCube()
 */
cube * copyCube(cube * self);

/**
 * Returns true if both cubes are equivalent.
 *
 * This function implements an equality check between cubes.
 * Both cubes are copied and redressed, and then compared.
 * Two cubes are equal if the combination is the same, even if they are not
 * oriented in the same direction.
 *
 * @param aCube Reference cube. Is self when called with
 *  aCube->equals(aCube, bCube)
 * @param bCube Cube to compare to aCube
 *
 * @returns true if cubes are equivalent, false else
 */
bool cubeIsEqual(cube * aCube, cube * bCube);

/**
 * Helper function to print cube map to stderr.
 *
 * Function may be called by aCube->print(aCube)
 * @param self cube to print to stderr.
 */
void printCube(cube * self);

/**
 * Function to delete cube properly and avoid memory leaks
 * @param self pointer to cube to delete
 */
void destroyCube(cube * self);

cube* voidCube(cube *self);
#endif
