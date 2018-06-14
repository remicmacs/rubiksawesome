# TODO
* Define coding guidelines
* Choose linter and use pre-commit hook (**Rémi**)
* ~~Set up GitLab server (**Alex**)~~
* ~~Choose graphical engine/library (**Rodolphe**)~~
* ~~Define data structure representing RCube's **state** (**Rémi**)~~
* ~~Create model for 3D representation (**Rodolphe**)~~
* ~~Find website for cube manipulation (**Alex**)~~
* ~~Define file structure hierarchy (folders `src`, `build`, `test`)~~
* ~~Create bulk string command parser~~

## Main controller

* ~~Setup~~
 * ~~3D Cube visualisation~~
 * ~~Models initialization~~
 * ~~User input interface setup~~
 * ~~Return to main loop~~
* Main loop?
 * ~~User input acquisition via SDL~~
 * ~~Command dispatch to controller (dripping down)~~
 * ~~Command dispatch to view (Bubbling up)~~
 * ~~Store command to history~~
 * ~~Move positionCube from model to controller~~

## Data manipulation

* ~~Rotations~~
 * ~~F~~
 * ~~B~~
 * ~~R~~
 * ~~L~~
 * ~~U~~
 * ~~D~~
 * ~~x~~
 * ~~y~~
 * ~~z~~
* ~~Rotation modifiers~~
 * ~~Counter-clockwise~~
 * ~~Double~~

## Documentation
* Tools justifications
 * GitLab
 * Linter
 * 3D library
 * Why dropping unit test framework ? How to use it next time ?
 * Why not using `indent` : powerful tool but limitations
 * Too many unknown tools = devops fatigue. We used GitLab + make it is a good
   start
* Task repartition
 * Rodolphe xp on 3D representation
 * Alexandre on algorithm resolutions (xp with Rubikscube)
* Use Cases and Data flow
* Diagrams
* Design choices : double model, MVC structure
* Main functions
 * Why a pattern comparator
 * Why a function to orientate the cube
 * Function to find a command to orientate the cube. (Justification of single
   responsability principle.
 * Why a queue for communication

## Tools
* ~~Makefile~~
* ~~.gitignore~~
