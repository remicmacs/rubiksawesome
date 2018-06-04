#ifndef CUBELET
#define CUBELET
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "cube.h"

/*
 * Tiles related functions
 */

typedef struct tile{
int face;
int row;
int col;
}tile;

typedef struct adjacentTiles{
tile tiles[2];
int nb;
}adjacentTiles;

/**
 * Draw a cube pattern with the selected tile
 */
void printTile(cube *self, tile elt);

/**
 * Get adjacent(s) tile(s)
 */
adjacentTiles getAdjacentTiles(cube *self, tile elt);
/**
 * Return the color of the given tile
 */
char getColorTile(cube *self, tile elt);
 


/***************************
 * Edges related functions
 ***************************/

typedef struct edge{
		tile tiles[2];
	}edge;

typedef struct adjacentFaces{
		int faces[2];
		int nb;
}adjacentFaces;

/**
 * Test if the given tile is an edge
 */
bool isEdge(tile elt);

/**
 * Define an edge thanks to his adjacent tile
 */
edge defineEdge(cube *self, tile elt);

/**
 * Print given edge
 */
void printEdge(cube *self, edge elt);

/**
 * Test if one of the edge’s tiles is on the selected face
 */
bool isEdgeOnFace(edge elt, int face);


/***************************
 * Corner related functions
 ***************************/

typedef struct corner{
		tile tiles[3];
	}corner;


/**
 * Define a corner thanks to his adjacents tiles.
 */
corner defineCorner(cube *self, tile elt);

/**
 * Print given corner 
 */
void printCorner(cube *self, corner elt);

/**
 * Verify if the given tile corresponding to a corner.
 */
bool isCorner(tile elt);


/**
 * Test if one of the edge’s tiles is on the selected face
 */
bool isCornerOnFace(corner elt, int face);



/****************************
 * Misc
 ***************************/

/**
 * Get the face(s) adjacent to the given tile
 */ 
adjacentFaces getAdjacentFaces(tile elt);

/**
 * Test if the given tile is a center
 */
bool isCenter(tile elt);


char getFaceColor(cube *self, tile elt);
//corner searchCorner(cube *self, char color0, char color1, char color2);

#endif
