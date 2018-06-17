# Animations

## Animating a movement

A movement in the cube can be comprised of one, two or three slices. For each slice, we have to create an `animation` and put it in an `animationStack`. The `animationStack` is a structure that can be chained into a list and is used to group animations to update all of them on each frame. Using a list for the `animationStack` allows us to enqueue them and execute them serially.

We can attribute a sound to be played upon starting the animationStack.

To synchronize the rotation of the view's data with the end of an animation, we use a callack called `onFinished`. This way we can act on the view without having to include `view.h` in `animations.h`.