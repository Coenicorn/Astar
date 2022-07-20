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

#include <grid.h>
#include <astar.h>
#include <cell.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int numDots = 1;

    // command line arguments lesgooo
    // taking input in c is a pain -_-
    if (argc != 2 || strlen(argv[1]) != 1 || !isdigit(argv[1][0]))
    {
        printf("Expected one digit for the number of dots in the grid!\n");
        return 1;
    }
    else
    {
        numDots = argv[1][0] - '0';
    }

    const int width = 10, height = 10;
    const int startX = 0, startY = 0;
    const int goalX = width - 1, goalY = height - 1;

    // to record the time it took to run the program
    time_t start, stop;

    // initialize random number generator, pretty important as the getGrid() function uses it
    srand(time(NULL));

    // initialize grid
    Grid *g = getGrid(width, height, numDots);

    printGrid(g);

    // visually seperate the "vanilla" grid and the solved one
    printf("<----------------------------------------------->\n");

    // to record the path
    Cell *path[MAX_PATH_LENGTH];

    // how fast is it really?
    start = clock();

    int fail = getPath(g, startX, startY, goalX, goalY, path);

    // probably slower than it COULD be
    stop = clock();

    if (!fail)
    {
        printGrid(g);

        // time in clock sycles divided by CLOCKS_PER_SEC is time in seconds, which if multiplied by 1000 gives time in milliseconds,
        // which is clearer to cool programmers like myself than seconds
        printf("\nProgram took %f milliseconds to complete\n", (double)(stop - start) / CLOCKS_PER_SEC * 1000);
    }
    else
        printf("No path possible!\n");

    // memory safety is badass!
    freeGrid(g);

    return 0;
}