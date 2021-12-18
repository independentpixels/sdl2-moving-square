# SDL2 How to Create a SDL2 Square the Moves and Bounces

This is a sample SDL2 project with a green square that can be moved on the screen using the keyboard directional keys.

The square can also have is speed increased or decreased.

Also, a simple off-screen detection is implemented in order to not allow the square going off-screen.

And finally, when the square hits the edges of the screen, it bounces in the opposite direction.

A video tutorial is available on youbute with the step-by-step.

[Video Tutorial](https://youtu.be/ccmejJdylYs)

## Pre-requisites

The project template comes with the links already setup pointing to the original location of the SDL2 and SLD2_image libraries.

On Mac:

You can use the commands below to install both libraries to the default location.

`$ brew install sdl2 sdl2_image`

Both libraries will be installed to `/urs/local/Cellar` and their paths will be already linked in the project.

On Linux (PopOS recommended):

You can use the commands below to install both libraries to the default location.

`sudo apt install libsdl2-dev`

`sudo apt install libsdl2-image-dev`

Alternatively you can already install the other libraries you might need in the future.

`sudo apt install libsdl2-mixer-dev`

`sudo apt install libsdl2-ttf-dev`

`$ brew install sdl2 sdl2_image`

The header files can be found at `/usr/include/SDL2`.

**Important:** Because now the symbolik links will have incorrect paths, you can just delete them. On Linux, the Makefile is configured to include the header files directly from the default include directory mentioned above.


## Building the application

This template uses as Makefile that was configured to build our application into the `build/debug` directory.

On Mac:

Use the existing `Makefile`.

On Linux:

- Rename the current make file to `Makefile.mac`.
- Rename `Makefile.linux` to `Makefile`.

In order to build the application, type:

`$ make`

## Running the application

In order to run the application, type:

`$ ./build/debug/play`

You should see the the application running.

## LICENSE

[MIT](https://mit-license.org)
