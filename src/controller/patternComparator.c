#include "patternComparator.h"

_Bool patternMatches(cube * aCube, cube * refPattern) {
    if (!aCube || !refPattern) {
        return false;
    } // If a pointer is NULL, returns

    // Make copies of cubes
    cube * currentCube = aCube->copy(aCube);
    cube * pattern = refPattern->copy(refPattern);

    // Redress cubes in the same orientations
    char frontFace = currentCube->cube[F][1][1];
    char upFace = currentCube->cube[U][1][1];
    positionCube(pattern, frontFace, upFace);

    // Copy blank spaces to aCube copy
    for(int face = F ; face <= D ; face++) {
        for(int index = 0; index < 3 ; index++) {
            for(int jindex = 0; jindex < 3; jindex++) {
                char color;
                if ((color = pattern->cube[face][index][jindex]) == ' ') {
                    currentCube->cube[face][index][jindex] = color;
                }
            }
        }
    }
    _Bool comparison = currentCube->equals(currentCube, pattern);

    // free copies
    free(currentCube);
    free(pattern);
    return comparison;
}

char * positionCommand(cube * aCube, char frontFace, char upFace) {
    if (frontFace == upFace) {
        exitFatal("in positionCommand(), the two faces have to be different");
    } // Exit condition if function not properly invoked

    char * command = "";
    bool firstMove = false;
    cube * copy = aCube->copy(aCube); // Copying data
    int commandSize = 0;

    // Fixing front center position : two axes are solved
    // 6 positions are possible, with only one valid

    // finding frontFace center
    int frontPos = F - 1;
    while(copy->cube[++frontPos][1][1] != frontFace); 

    if (frontPos != F) {
        firstMove = !firstMove;
        commandSize = 4;
        command = (char *) malloc(sizeof(char)*commandSize);
        switch(frontPos) {
            case(R):
                strncpy(command, "y ", 3);
                copy->rotate(copy, y);
                break;
            case(L):
                strncpy(command, "yi ", 4);
                copy->rotate(copy, yi);
                break;
            case(U):
                strncpy(command, "xi ", 4);
                copy->rotate(copy, xi);
                break;
            case(D):
                strncpy(command, "x ", 3);
                copy->rotate(copy, x);
                break;
            case(B):
                strncpy(command, "x2 ", 4);
                copy->rotate(copy, x2);
                break;
        }
    } else {
        command = (char *) malloc(sizeof(char));
        strncpy(command, "",1);
    } // According to frontFace center position, choose command

    *(command+commandSize-1) = '\0'; // adding an endmark for safety's sake

        // Fixing up center position : only one axis has to be solved
    // 4 positions are possible, with only one valid
    int upPos = R - 1;
    while(copy->cube[++upPos][1][1] != upFace);
    if (upPos != U) {
        commandSize += 4;
        command = (char *) realloc(command, sizeof(char) * commandSize);
        switch(upPos) {
            case(L):
                strncat(command, "z ", 3);
                copy->rotate(copy, z);
                break;
            case(D):
                strncat(command, "z2 ", 4);
                copy->rotate(copy, z2);
                break;
            case(R):
                strncat(command, "zi ", 4);
                copy->rotate(copy, zi);
                break;
        }
    }
    destroyCube(copy); // Freeing data copy
    return command;
}

move * positionCmd(cube * aCube, char frontFace, char upFace) {
    char * cmd = positionCommand(aCube, frontFace, upFace);
    move * moves = commandParser(cmd);
    return moves;
}

cube * positionCube(cube * aCube, char frontFace, char upFace) {
    char * commands = positionCommand(aCube, frontFace, upFace);
    if (commands == NULL) {
        return aCube;
    } // Recovering command to position cube


    char * token = strtok(commands, " ");
    int i = 0;
    move moves[2] = {-1, -1};
    while (i < 2 && token) {
        moves[i] = mapCodeToMove(token);
        token = strtok(NULL, " ");
        i++;
    } // Command tokenization and parsing to enum move

    i = -1;
    while(++i < 2 && (int) moves[i] != -1) {
        aCube->rotate(aCube, moves[i]);
    } // Excution of commands
    return aCube;
}

/**
 * Function to bring center cublets in standard position.
 * Standard position of center cublets are :
 *  * green on front
 *  * blue on back
 *  * red on right
 *  * orange on left
 *  * white on top
 *  * yellow on down
 *
 *  This function is a helper to the cubeIsEqual function.
 *
 *  @param aCube Reference to cube to be redressed
 *  @returns Reference to redressed cube
 */
cube * redressCube(cube * aCube) {
    aCube = positionCube(aCube, 'g', 'w');
    return aCube;
}

