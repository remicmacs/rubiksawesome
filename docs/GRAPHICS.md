# Graphics

## Lighting

The lighting uses ambiant, diffuse and specular lighting. Ambiant lighting is a small constant color that is applied on every materials and mimic the light scattering. Diffuse lighting is a change in color depending on the difference between the light direction and the normal of the face being illuminated. Specular lighting is a change in color depending on the difference between the reflected lightray and the position of the viewer. When combined, those three types of lighting is enough to render a lot of materials. By setting the parameters for each of these lightings, we can make different materials.

![Lighting](img/lighting.png)

We set the light parameters in the `generateView()` function. Setting the light parameters is done by setting the colors (in RGBA) of the ambiant, diffuse and specular light. We usually set them all to white with more or less power.

After setting the light parameters, we need to set the material parameters before drawing the objects. The material parameters describes how the material reacts to each type of lights. Because of the types of lights used (diffuse and specular), we need to correctly set the normal vector of the face that is going to be drawn. As described in [VIEW](./VIEW.md), in our program, each face has a normal vector set upon generation.

## Creating the rubik's cube

The rubik's cube is just a 3x3x3 matrix of cubes. This model allows us to access or modify a slice by fixing one of the coordinates and iterate through all the others. The `rotateDataX()`, `rotateDataY()` and `rotateDataZ()` functions uses this to access a slice as a 3x3 matrix and rotate it.

## Creating the cubes

The cubes are generated as a group of 6 faces. On intialization, for each of the 27 cubes contained within the rubik's cube (we draw the center cube even if it is not visible nor usable), we generate 6 faces with the `generateFace()` function.

The `generateFace()` function will create a face which coordinates and colour depends on the type of the face (`FaceType` enum). We'll then apply an offset and a scale factor to the face. The offset is the parent cube position. When the face is done, we'll save the vertices positions to be reused by the animations. Each face also have a normal vector that must be set correctly to have the light working realistically.