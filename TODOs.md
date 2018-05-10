# TODO

* Define coding guidelines
* Choose linter and use pre-commit hook (**Rémi**)
* Set up GitLab server (**Alex**)
* Choose unit test framework and write howto (**Rémi**)
* Choose graphical engine/library (**Rodolphe**)
* Define data structure representing RCube's **state** (**Rémi**)
* Define **controller** functions to control cube validity (**Alex**)
* Find website for cube manipulation
* Define file structure hierarchy (folders `src`, `build`, `test`)

* Data manipulation
 * Rotations :
  * F
  * R
  * U
  * B
  * L
  * D
  * F'
  * R'
  * U'
  * B'
  * L'

Each rotation is a clockwise or counter-clockwise rotation for the face which is
rotating but also a swapping of colors on connected edges

* Documentation
 * Tools justifications
  * GitLab
  * Linter
  * 3D library
  * Unit test framework
 * Task repartition
  * Rodolphe xp on 3D representation

* Tests
 * 4 times the same move is like nothing happened
 * One operation and its complement cancel out each other

## Gotchas
* Corners and edges that are linked
