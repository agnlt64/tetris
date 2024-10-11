# C++ Tetris Game using Raylib

# Build

## Windows
```console
g++ src/*.cpp -o bin/tetris -I./src/include -L./lib -lraylib -lopengl32 -lwinmm -lgdi32
```
Make sure to have the [raylib](https://github.com/raysan5/raylib) DLLs into the `lib` folder.

## macOS / Linux
```console
g++ src/*.cpp -o bin/tetris -I./src/include -L/path/to/raylib -lraylib
```

# Credits
Original repo [here](https://github.com/educ8s/Cpp-Tetris-Game-with-raylib).

## Music
1st part : https://www.youtube.com/watch?v=_y_Vq7-eAtY  
2nd part : https://www.youtube.com/watch?v=63hoSNvS6Z4
3rd part : https://www.youtube.com/watch?v=7TqGvfx1Xvs  