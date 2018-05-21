# TODO
* Define coding guidelines
* Choose linter and use pre-commit hook (**Rémi**)
 ~~~Set up GitLab server (**Alex**)~~~
* Choose unit test framework and write howto (**Rémi**)
* ~~~Choose graphical engine/library (**Rodolphe**)~~~
* ~~~Define data structure representing RCube's **state** (**Rémi**)~~~
* ~~~Create model for 3D representation (**Rodolphe**)~~~
* Define **controller** functions to control cube validity (**Alex**)
* ~~~Find website for cube manipulation (**Alex**)~~~
* Define file structure hierarchy (folders `src`, `build`, `test`)
* ~~~Create bulk string command parser~~~

## Main controller
* Setup
 * 3D Cube visualisation
 * Models initialization
 * User input interface setup
 * Return to main loop
* Main loop?
 * User input acquisition
 * Command resolution & validity control
 * Command dispatch to models
 * Command dispatch to view
 * Store command to history
 * ~~~Move positionCube from model to controller~~~

## Data manipulation
* Rotations
 * F
 * B
 * R
 * L
 * U
 * D
 * x
 * y
 * z
* Rotation modifiers
 * Counter-clockwise
 * Double

## Documentation
* Tools justifications
 * GitLab
 * Linter
 * 3D library
 * Unit test framework
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

## Tests
* 4 times the same move is like nothing happened
* One operation and its complement cancel out each other (Color model)
