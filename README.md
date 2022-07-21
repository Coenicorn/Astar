# A* Pathfinding in C

This is a little c project I wrote while on holiday in scotland (it's beautiful, 
you should visit there!).

I'm sure someone smarter than me could have written this waaaay better than I
have, but I don't really care, I had fun!

If you want to take a look at the code, it's in the src directory (duh ;)

If you want to run the program, run the "make" command in the src directory. This will
build an executable into the build directory. It IS written in linux, so I'm not sure if 
it'll run on windows, but I'm sure you'll figure it out ;)
You can then run it by running (assuming you're in the astar directory):

```
./build/main 0
```

to run the program.
It takes one command line argument; the amount of obstacles in the grid.
This is a single digit, so no higher than 9 I'm afraid!

***Since the program generates the obstacles randomly, there is a chance that the start of end is
completely blocked, and a path is thus impossible, in which case the program will output "No path possible!". 
You might have to run it a few times to get a randomly generated grid where a path is possible.***

The default size of the grid is 10x10, but you can alter this in the "main.c" file:

```
...
const int width = 10, height = 10;
...
```

***The program doesn't stop you from running it with stupidly large grids, so with very
large grids this program will suck up all of your precious memory, so watch out with that!***

If you're able to run the code, I'm sure you're smart enough to alter some source code ;)

Thanks for reading this lol, didn't expect anyone to do that tbh

## Static library

To use the static library, copy the files in lib_files. There's a header (.h) and a library (.a) file in there.
To compile with these, link with the .a file with flag "-lastar", and include the .h file. That should be it!
If you don't know what linking is, what are you doing here? (jk, look it up, it's not that difficult ;))