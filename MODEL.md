# Model
The data model implemented in the program makes the distinction between the
color of the faces and the position of the cublets.

## cube.c
The file `cube.c` implements a pattern mapping of the colors of the **54
faces**. The data structure is a list of the **six faces** each composed of **9
cublets faces**.
This data model is inherently in 2 dimensions, just as an open die pattern

**INSERT cube pattern here**

### enum `move`
Mapping of all implemented cube rotations.

### Data structure
Mocked object modelisation of data. The data structure carries its interface
with it. Attempt of data encapsulation : hidden logic enforces that data
manipulation is done correctly.

### Public interface
**rotate** : implemented moves = 
**copy** : returns a deep copy of the cube passed
**equals** : compares two cubes (@TODO: explain what conditions are checked)
**print** : debug method to print cube pattern to stderr

## Other data structure
3D mapping of pointers to 3D cubes.
