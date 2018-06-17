#include <stdio.h>
#include <string.h>
#include "cubelet.h"
#include <stdbool.h>

bool isEdge(tile elt){
    int edges[4][2] = {
        {0, 1}, {1, 0},
        {1, 2}, {2, 1}
    };
    for (int i=0;i < 4;i++){
        if(edges[i][0] == elt.row && edges[i][1] == elt.col){
            return true;
        }
    }
    return false;
}

bool isCorner(tile elt){
    int corners[4][2] = {
        {0, 0}, {0, 2},
        {2, 0}, {2, 2}
    };
    for (int i=0;i < 4;i++){
        if(corners[i][0] == elt.col && corners[i][1] == elt.row){
            return true;
        }
    }
    return false;
}

bool isCenter(tile elt){
    if(elt.row == 1 && elt.col == 1){
        return true;
    }
    return false;
}

adjacentFaces getAdjacentFaces(tile elt){
    int i=0;
    adjacentFaces adj;

    switch(elt.face){
        case(F):
            if(elt.row == 0){adj.faces[i] = U; i++;}
            if(elt.row == 2){adj.faces[i] = D; i++;}
            if(elt.col == 0){adj.faces[i] = L; i++;}
            if(elt.col == 2){adj.faces[i] = R; i++;}

            break;
        case(B):
            if(elt.row == 0){adj.faces[i] = U; i++;}
            if(elt.row == 2){adj.faces[i] = D; i++;}
            if(elt.col == 0){adj.faces[i] = R; i++;}
            if(elt.col == 2){adj.faces[i] = L; i++;}
            break;
        case(R):
            if(elt.row == 0){adj.faces[i] = U; i++;}
            if(elt.row == 2){adj.faces[i] = D; i++;}
            if(elt.col == 0){adj.faces[i] = F; i++;}
            if(elt.col == 2){adj.faces[i] = B; i++;}
            break;
        case(L):
            if(elt.row == 0){adj.faces[i] = U; i++;}
            if(elt.row == 2){adj.faces[i] = D; i++;}
            if(elt.col == 0){adj.faces[i] = B; i++;}
            if(elt.col == 2){adj.faces[i] = F; i++;}
            break;
        case(U):
            if(elt.row == 0){adj.faces[i] = B; i++;}
            if(elt.row == 2){adj.faces[i] = F; i++;}
            if(elt.col == 0){adj.faces[i] = L; i++;}
            if(elt.col == 2){adj.faces[i] = R; i++;}
            break;
        case(D):
            if(elt.row == 0){adj.faces[i] = F; i++;}
            if(elt.row == 2){adj.faces[i] = B; i++;}
            if(elt.col == 0){adj.faces[i] = L; i++;}
            if(elt.col == 2){adj.faces[i] = R; i++;}
            break;
    }

    adj.nb = i;
    return adj;
}

adjacentTiles getAdjacentTiles(tile elt)
{
    // Lookup table of each 27 faces to their adjacent tiles
    adjacentTiles tiles[6][3][3] =
    {
        // F
        {
            { //0
                { //0
                    {
                        {U,2,0},
                        {L,0,2}
                    },
                    2
                },
                { //1
                    {
                        {U,2,1},
                        {0}
                    },
                    1
                },
                { // 2
                    {
                        {U,2,2},
                        {R,0,0}
                    },
                    2
                }
            },
            { // 1
                { // 0
                    {
                        {L,1,2},
                        {0}
                    },
                    1
                },
                { // 1
                    {
                        {0},
                        {0}
                    },
                    0
                },
                { // 2
                    {
                        {R,1,0},
                        {0}
                    },
                    1
                }
            },
            { // 2
                { // 0
                    {
                        {L,2,2},
                        {D,0,0}
                    },
                    2
                },
                { // 1
                    {
                        {D,0,1},
                        {0}
                    },
                    1
                },
                { // 2
                    {
                        {R,2,0},
                        {D,0,2}
                    },
                    2
                }
            }
        },
        { // B
            { // 0
                { //0
                    {
                        {R,0,2},
                        {U,0,2}
                    },
                    2
                },
                { // 1
                    {
                        {U,0,1},
                        {0}
                    },
                    1
                },
                { // 2
                    {
                        {U,0,0},
                        {L,0,0}
                    },
                    2
                }
            },
            { // 1
                { // 0
                    {
                        {R,1,2},
                        {0}
                    },
                    1
                },
                { // 1
                    {
                        {0},
                        {0}
                    },
                    0
                },
                { // 2
                    {
                        {L,1,0},
                        {0}
                    },
                    1
                }
            },
            { // 2
                { // 0
                    {
                        {R,2,2},
                        {D,2,2}
                    },
                    2
                },
                { // 1
                    {
                        {D,2,1},
                        {0}
                    },
                    1
                },
                { // 2
                    {
                        {D,2,0},
                        {L,2,0}
                    },
                    2
                }
            }
        },
        { // R
            { // 0
                { // 0
                    {
                        {F,0,2},
                        {U,2,2}
                    },
                    2
                },
                { // 1
                    {
                        {U,1,2},
                        {0}
                    },
                    1
                },
                { // 2
                    {
                        {U,0,2},
                        {B,0,0}
                    },
                    2
                }
            },
            { // 1
                { // 0
                    {
                        {F,1,2},
                        {0}
                    },
                    1
                },
                { // 1
                    {
                        {0},
                        {0}
                    },
                    0
                },
                { // 2
                    {
                        {B,1,0},
                        {0}
                    },
                    1
                }
            },
            { // 2
                { // 0
                    {
                        {F,2,2},
                        {D,0,2}
                    },
                    2
                },
                { // 1
                    {
                        {D,1,2},
                        {0}
                    },
                    1
                },
                { // 2
                    {
                        {D,2,2},
                        {B,2,0}
                    },
                    2
                }
            }
        },
        { // L
            { // 0
                { // 0
                    {
                        {B,0,2},
                        {U,0,0}
                    },
                    2
                },
                { // 1
                    {
                        {U,1,0},
                        {0}
                    },
                    1
                },
                { // 2
                    {
                        {U,2,0},
                        {F,0,0}
                    },
                    2
                }
            },
            { // 1
                { // 0
                    {
                        {B,1,2},
                        {0}
                    },
                    1
                },
                { // 1
                    {
                        {0},
                        {0}
                    },
                    0
                },
                { // 2
                    {
                        {F,1,0},
                        {0}
                    },
                    1
                }
            },
            { // 2
                { // 0
                    {
                        {B,2,2},
                        {D,2,0}
                    },
                    2
                },
                { // 1
                    {
                        {D,1,0},
                        {0}
                    },
                    1
                },
                { // 2
                    {
                        {D,0,0},
                        {F,2,0}
                    },
                    2
                }
            }
        },
        { // U
            { // 0
                { // 0
                    {
                        {L,0,0},
                        {B,0,2}
                    },
                    2
                },
                { // 1
                    {
                        {B,0,1},
                        {0}
                    },
                    1
                },
                { // 2
                    {
                        {B,0,0},
                        {R,0,2}
                    },
                    2
                }
            },
            { // 1
                { // 0
                    {
                        {L,0,1},
                        {0}
                    },
                    1
                },
                { // 1
                    {
                        {0},
                        {0}
                    },
                    0
                },
                { // 2
                    {
                        {R,0,1},
                        {0}
                    },
                    1
                }
            },
            { // 2
                { // 0
                    {
                        {L,0,2},
                        {F,0,0}
                    },
                    2
                },
                { // 1
                    {
                        {F,0,1},
                        {0}
                    },
                    1
                },
                { // 2
                    {
                        {F,0,2},
                        {R,0,0}
                    },
                    2
                }
            }
        },
        { // D
            { // 0
                { // 0
                    {
                        {L,2,2},
                        {F,2,0}
                    },
                    2
                },
                { // 1
                    {
                        {F,2,1},
                        {0}
                    },
                    1
                },
                { // 2
                    {
                        {F,2,2},
                        {R,2,0}
                    },
                    2
                }
            },
            { // 1
                { // 0
                    {
                        {L,2,1},
                        {0}
                    },
                    1
                },
                { // 1
                    {
                        {0},
                        {0}
                    },
                    0
                },
                { // 2
                    {
                        {R,2,1},
                        {0}
                    },
                    1
                }
            },
            { // 2
                { // 0
                    {
                        {L,2,0},
                        {B,2,2}
                    },
                    2
                },
                { // 1
                    {
                        {B,2,1},
                        {0}
                    },
                    1
                },
                { // 2
                    {
                        {B,2,0},
                        {R,2,2}
                    },
                    2
                }
            }
        }
    };
    return tiles[elt.face][elt.row][elt.col];
}

edge defineEdge(tile elt){
    adjacentTiles adjtile = getAdjacentTiles(elt);
    edge newedge = {{elt, adjtile.tiles[0]}};
    return newedge;
}


void printTile(cube *self, tile elt)
{
    cube * pattern = copyCube(self);
    pattern = voidCube(pattern);
    pattern->cube[elt.face][elt.row][elt.col] = self->cube[elt.face][elt.row][elt.col];
    pattern->print(pattern);
    printf("{f:%d,r:%d,c:%d}\n",elt.face,elt.row,elt.col);
    destroyCube(pattern);

}

void printEdge(cube *self, edge elt)
{
    fprintf(stderr, "\n-- Display Edge --\n");
    cube * pattern = copyCube(self);
    pattern = voidCube(pattern);
    for(int i=0; i< 2;i++){
        pattern->cube[elt.tiles[i].face][elt.tiles[i].row][elt.tiles[i].col] = self->cube[elt.tiles[i].face][elt.tiles[i].row][elt.tiles[i].col];
    }
    pattern->print(pattern);
    for(int i=0; i< 2;i++){
        fprintf(stderr, "{f:%d,r:%d,c:%d}\n",elt.tiles[i].face,elt.tiles[i].row,elt.tiles[i].col);
    }
    fprintf(stderr, "--------------------\n");
    destroyCube(pattern);
}

char getColorTile(cube *self, tile elt)
{
    return self->cube[elt.face][elt.row][elt.col];
}

char getFaceColor(cube *self, tile elt){
    return self->cube[elt.face][1][1];
}

bool isEdgeOnFace(edge elt, int face)
{
    for(int i=0; i < 2; i++)
    {
        if(elt.tiles[i].face == face){
            return true;}
    }
    return false;
}

bool isCornerOnFace(corner elt, int face)
{
    for(int i=0; i < 3; i++)
    {
        if(elt.tiles[i].face == face){
            return true;}
    }
    return false;
}


corner defineCorner(tile elt){
    adjacentTiles adjtile = getAdjacentTiles(elt);
    corner newcorner = {{elt, adjtile.tiles[0], adjtile.tiles[1]}};
    return newcorner;
}


void printCorner(cube *self, corner elt)
{
    fprintf(stderr, "\n-- Display Corner --\n");
    cube * pattern = copyCube(self);
    pattern = voidCube(pattern);
    for(int i=0; i< 3;i++){
        pattern->cube[elt.tiles[i].face][elt.tiles[i].row][elt.tiles[i].col] = self->cube[elt.tiles[i].face][elt.tiles[i].row][elt.tiles[i].col];

    }
    pattern->print(pattern);
    for(int i=0; i< 3;i++){
        fprintf(stderr, "{f:%d,r:%d,c:%d}\n",elt.tiles[i].face,elt.tiles[i].row,elt.tiles[i].col);
    }
    fprintf(stderr, "--------------------\n");
}
