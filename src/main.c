/*

C implementation of the A* pathfinding algorithm.
Probably way longer than it needs to be, but frankly, I don't really care lol.

To use this implementation, define a grid (as per the Grid struct) and call the getPath() function with
correct arguments.

There is a path returned (an array of pointers to the cells in the grid) but I don't use it as this implementation is mostly just to look cool
and for me to feel slightly good about my programming skills (which is very illjustified lol).

If you're actually reading this, enjoy! (What are you doing tho?)

As for other programmers reading this:

The maximum time complexity of this program is still the same as that of floodfill,
because in the worst case scenario you'll still have to traverse all the cells in the grid.
The best case scenario is quite a bit better though, as the heuristic kind of "guides" the pathfinding
towards the target as opposed to just filling everything and randomly stumbling across the
path like floodfill does.

The space complexity is pretty bad, as all the cells in the grid are stored in memory and the
open array has a fixed size. Still, a pretty cool algorithm if you'd ask me!

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "grid.h"
#include "astar.h"
#include "cell.h"

int main(int argc, char *argv[])
{
    int numObst;

    // command line arguments lesgooo
    // taking input in c is a pain -_-
    if (argc != 2)
    {
        printf("Expected one digit for the number of obstacles in the grid!\n");
        return 1;
    }
    else
    {
        numObst = atoi(argv[1]);

        if (numObst < 0)
        {
            printf("Expected a positive number for number of obstacles in the grid!\n");
            return 1;
        }
    }
                                                                                            
    const int width = 30, height = 30;
    const int startX = 0, startY = 0;
    const int goalX = width - 1, goalY = height - 1;

    // initialize random number generator, pretty important as the getGrid() function uses it
    int seed = (int)time(NULL);
    srand(seed);

    // initialize grid
    Grid *g = getRandomGrid(width, height, numObst);

    printf("Initial grid:\n");
    printGrid(g);

    // to record the path
    Cell *path[MAX_PATH_LENGTH];
    // fill with initial 0s
    for (int i = 0; i < MAX_PATH_LENGTH && (path[i] = NULL); i++)
        path[i] = NULL;

    // to record the time it took to run the program
    time_t start, stop;

    // how fast is it really?
    start = clock();

    int fail = pathfind(g, startX, startY, goalX, goalY, path);

    // probably slower than it COULD be
    stop = clock();

    if (!fail)
    {
        printf("Finished path:\n");
        printGrid(g);

        // time in clock sycles divided by CLOCKS_PER_SEC is time in seconds, which if multiplied by 1000 gives time in milliseconds,
        // which is clearer to cool programmers like myself than seconds
        printf("Pathfinding took %f milliseconds \n", (float)(stop - start) / CLOCKS_PER_SEC * 1000);
        printf("Seed used: %d, with %d obstacles\n", seed, numObst);
    }
    else
        printf("Program error!\n");

    // memory safety is badass!
    freeGrid(g);

    return 0;
}

// piece of code to test the speed of the algorithm, no idea if this is accurate or not, but it sure is something
// int main()
// {
//     int w = 1000, h = 1000, obstacles = 20, seed = 1658413074, num_clocks = 0, num_iter = 10000;
//     int sX = 0, sY = 0, gX = w-1, gY = h-1;
//     time_t start, stop;
//     Grid *g;


//     for (int i = 1; i <= num_iter; i++)
//     {
//         srand(seed);

//         g = getGrid(w, h, obstacles);

//         Cell *path[MAX_PATH_LENGTH];
//         for (int j = 0; j < MAX_PATH_LENGTH; j++)
//             path[j] = NULL;

//         start = clock();
//         pathfind(g, sX, sY, gX, gY, path);
//         stop = clock();

//         num_clocks += (int)stop - (int)start;

//         printf("Done %d of %d\n", i, num_iter);

//         freeGrid(g);
//     }

//     float finished_time_millis = (float)num_clocks / (float)CLOCKS_PER_SEC / (float)num_iter * 1000.0;

//     printf("Finished with average time of %f milliseconds\n", finished_time_millis);
// }