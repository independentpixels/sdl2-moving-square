# SDL2 How to Create a SDL2 Square the Moves and Bounces

This is a sample SDL2 project with a green square that can be moved on the screen using the keyboard directional keys.

The square can also have is speed increased or decreased.

Also, a simple off-screen detection is implemented in order to not allow the square going off-screen.

And finally, when the square hits the edges of the screen, it bounces in the opposite direction.

A video tutorial is available on youbute with the step-by-step.

[Video Tutorial](https://youtu.be/ccmejJdylYs)

## Pre-requisites

The project template comes with the links already setup pointing to the original location of the SDL2 and SLD2_image libraries.

You can use the commands below to install both libraries to the default location.

`$ brew install sdl2 sdl2_image`

Both libraries will be installed to `/urs/local/Cellar` and their paths will be already linked in the project.

## Building the application

This template uses as Makefile that was configured to build our application into the `build/debug` directory.

In order to build the application, type:

`$ make`

## Running the application

In order to run the application, type:

`$ ./build/debug/play`

You should see the string "Hello SDL2!" being printed to the console output.

## LICENSE

[MIT](https://mit-license.org)
