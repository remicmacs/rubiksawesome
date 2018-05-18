# Rubiksawesome
ISEN C Project
Rémi B.
Rodolphe H.
Alexandre T.

> Our whole life is solving puzzles.
>
> _<div style="text-align: right"> Erno Rubik </div>_

## Intro
Rubiksawesome is a Rubik's Cube 3x3x3 simulator with a 3D display and a solver
engine.
It is developped as a school project @ISEN-Lille.

## Key features
* Animated 3D model
* Command-line argument for bulk command parsing
* Solving algorithm implemented
 * Jessica Fridrich


## Requirements
As of today, Rubiksawesome is implemented for compilation with `gcc` on a
GNU/Linux system. **Windows is not supported, nor it ever will be**.

For documentation generation, `doxygen` is required.

CPU : core i7
RAM : 16 GB or more (program leaks AF)
GPU : Nvidia TITAN V

## How to use

```shell
# Clone repository
$ git clone ...

# Step into project folder
$ cd rubiksawesome

# Use make to build the project
$ make build

# Enjoy !
$ ./rubiksawesome
```

### Options
Command-line arguments
    -S

Step into project folder
See [`topic.pdf`](topic.pdf).

## Documentation
[`MODEL.md`](MODEL.md) : Description of data model.
[`RESOURCES.md`](RESOURCES.md) : Sources of inspiration.
[`TODOs.md`](TODOs.md) : What is done and not yet accomplished.

### File structure
> /  
> |  
> |-- src/  
> |     |  
> |     |-- model/  
> |     |-- view/  
> |     |-- controller/  
> |     |-- tests/  
> |     |-- main.c  
> |     |-- main.h  
> |  
> |-- build/  
> |-- docs/  
>
