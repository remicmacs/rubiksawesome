# Rubiksawesome

[![Works on my machine](https://img.shields.io/badge/Works-on%20my%20machine-green.svg)](https://shields.io/)
[![ISEN approved](https://img.shields.io/badge/ISEN-approved-green.svg)](https://shields.io/)
[![Made in C](https://img.shields.io/badge/Made%20in-C-1f425f.svg)](https://shields.io/)
[![Gluten free](https://img.shields.io/badge/Gluten-free-1f425f.svg)](https://shields.io/)
[![License CRAPL](https://img.shields.io/badge/License-CRAPL-blue.svg)](https://shields.io/)

<img align="right" src="docs/img/rubiks-cube.png" alt="drawing" width="128px"/>


Contributors:
* Rémi B.
* Rodolphe H.
* Alexandre T.

> Our whole life is solving puzzles.
>
> _<div style="text-align: right" width="200px"> [Erno Rubik] </div>_


## Intro
Rubiksawesome is a Rubik's Cube 3x3x3 simulator with a 3D display and a solver
engine.
It is developped as a school project @ISEN-Lille.

Here is a capture of the current state:
![Current state capture](docs/capture.png)


The objectives evaluated are available (in French) in the file linked below :
[`topic.pdf`](docs/topic.pdf).

## Key features
* 3D model
  * Rotations animations
  * Lighting
  * Texturing
  * Skybox
  * Mouse and keyboard inputs
  * Beautiful win screen
  * Marvelous Creative Commons sound effects
  * Display of the command history
  * Enabling/Disabling of command overlay
* Command-line arguments for game modes
    * Random scrambling (default)
    * Precise scramble
    * Non-scrambled cube
* Solving algorithms
  * Jessica Fridrich

## How to play

Move the view by clicking and dragging with your mouse.
The scroll wheel can be used to zoom/unzoom.

The keyboard shortcuts are:

Key | Function
--- | ---
`I` | Enable/Disable instructions
`Left Shift` | Rotate counterclockwise
`Left Ctrl` | Rotate 2 slices at once (lowercase moves)
`F` | Rotate front
`B` | Rotate back
`U` | Rotate up
`D` | Rotate down
`L` | Rotate left
`R` | Rotate right
`X` | Rotate the cube around X axis
`Y` | Rotate the cube around Y axis
`Z` | Rotate the cube around Z axis
`F2` | Start a new game
&#8679;&#8679;&#8681;&#8681;&#8678; &#8680;&#8678; &#8680;`B` `A` | Ask for help
`Esc` | Exit

## Requirements

Rubiksawesome needs:

```
SDL version: 2.0.8
OpenGL version: 3.0
```

and can be compiled using `gcc` on a GNU/Linux system.
**Windows is not supported, nor it ever will be**.

For documentation generation, `doxygen` is required.

### Recommended setup

* CPU : core i7
* RAM : 16 GB or more (program leaks AF)
* GPU : Nvidia TITAN V (ultimate quality may need a quantic GPU)

## How to use

```shell
# Clone repository
$ git clone ...

# Step into project folder
$ cd rubiksawesome

# Use make to build the project
$ make

# Enjoy !
$ ./rubiksawesome
```

### Options
```
$ ./rubiksawesome -h
```
outputs :

```
Usage is :
	./rubiksawesome [-option [scramble str]]
Options are
	-S [scramble str] : scramble the cube to a randomly generated scramble (default behavior)
		or to a scramble sequence passed as a double quote delimited string
	-C : start the came with a completed Rubik's Cube yours to scramble
```



## Documentation
[`MODEL.md`](docs/MODEL.md) : Description of data model.

[`CONTROLLER.md`](docs/CONTROLLER.md) : Core logic description

[`VIEW.md`](docs/VIEW.md) : 3D display, GUI and main user interface presentation

[`PROJECT.md`](docs/PROJECT.md) : Project planning and organization.

