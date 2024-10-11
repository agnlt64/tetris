# C++ Tetris Game using Raylib

# Quick start
Just go to the [releases page](https://github.com/agnlt64/tetris/releases) and download the appropriate binary file. 

# Build on Windows
```console
g++ src/*.cpp -o bin/tetris -I./src/include -L./lib -lraylib -lopengl32 -lwinmm -lgdi32
```
Make sure to have the [raylib](https://github.com/raysan5/raylib) DLLs into the `lib` folder.

# Build on macOS / Linux
```console
g++ src/*.cpp -o bin/tetris -I./src/include -L/path/to/raylib -lraylib
```
On Linux, if you have Raylib installed globally, you may not have to use `-L/path/to/raylib`.

# Controls
Move blocks `left` and `right` with the arrow keys. Hold to move faster. Use `up` to rotate the current block. Use `down` to make the current block go down by one row. Hold to go down faster. Press `M` to pause the music. 

# Credits
Original repo [here](https://github.com/educ8s/Cpp-Tetris-Game-with-raylib).

## Music
1st part : https://www.youtube.com/watch?v=_y_Vq7-eAtY  
2nd part : https://www.youtube.com/watch?v=63hoSNvS6Z4  
3rd part : https://www.youtube.com/watch?v=7TqGvfx1Xvs