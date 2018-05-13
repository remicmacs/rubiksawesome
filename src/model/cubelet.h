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
tile *tiles;
int nb;
}adjacentTiles;

/**
 * Draw a cube pattern with the selected tile
 */
void printTile(cube self, tile elt);

/**
 * Get adjacent(s) tile(s)
 */
adjacentTiles getAdjacentTiles(cube self, tile elt);

/**
 * Return the color of the given tile
 */
char getColorTile(cube self, tile elt);
 


/***************************
 * Edges related functions
 ***************************/

typedef struct edge{
		tile tiles[2];
	}edge;

typedef struct adjacentFaces{
		int *faces;
		int nb;
}adjacentFaces;

/**
 * Test if the given tile is an edge
 */
bool isEdge(tile elt);

edge defineEdge(cube self, tile elt);

void printEdge(cube self, edge elt);



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

char getFaceColor(cube self, tile elt);

#endif
