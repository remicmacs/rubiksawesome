# View

## Moving the cubes

When moving the cubes, 2 things have to be done:

* We need to move the vertices to update the view
* We need to move the cubes inside the 3x3x3 matrix to keep track of their positions

### Moving the vertices

Moving the vertices is done by the functions `rotateFaceX()`, `rotateFaceY()` and `rotateFaceZ()`. Those functions uses trigonometry to move each vertices around an axis. When this has been done, we save the new position into the vertices. Those functions allows a rotation of a given angle.

### Moving the matrices

Moving the matrices is done by the functions `rotateDataX()`, `rotateDataY()` and `rotateDataZ()`. A matrix has to be rotated 90° or -90° per movement. The techniques for easily rotating a matrix are as following:

* Rotating 90°
	1. Transpose the matrix
	2. Reverse each row of the matrix
* Rotating -90°
	1. Transpose the matrix
	2. Reverse each column of the matrix

## Updating the view

The view has an `update()` function that must be called on each iteration of the main loop. The update function fully redraw the view if needed and catch user inputs to send them back to the main program. The update does the following:

1. Update the animations list:
	* Start a new animation if needed
	* Update the current animation
	* Remove the current animation if it is finished
* Show the help window if needed
* Get and parse user input
* Clear the screen
* Place the camera
* Draw the skybox
* Draw the cubes
* Draw the instructions if needed
* Draw the history
* Draw the XYZ instruction
* Swap the window content
* Update the help window if needed:
	* Draw the content of the help window
	* Swap the content of the help window

See [GRAPHICS](./GRAPHICS.md) for more information on how the objects are drawn.

## Moving the camera

The `camera` structure holds the camera position in spherical coordinates. Those are projected into cartesian coordinates on drawing. Moving the mouse cursor increments or decrements the $\phi$ and $\theta$ angle. Using the scrollwheel increments or decrements the $r$ distance.

## The sound store

The sound store is a small structure that holds the pointers to the sound after they have been loaded by SDL_Mixer. We generate it during the view generation and allows anyone to access the sounds as long as they have access to the view.

## The texture store

The texture store is a structure holding all the texture that may be used in the program. We generate it during the view generation and it allows anyone to access the textures as long as they have access to the view. Generation of the texture store is described in [GRAPHICS](./GRAPHICS.md)

