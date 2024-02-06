#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <astar.h>

int main()
{
    const int width = 30, height = 30, numObst = 15;
    const int startX = 0, startY = 0;
    const int goalX = width - 1, goalY = height - 1;

    // initialize random number generator, pretty important as the getGrid() function uses it
    int seed = (int)time(NULL);
    srand(seed);

    // initialize grid
    ASTAR_Grid g;
    ASTAR_InitGrid(&g, width, height);

    printf("Initial grid:\n");
    ASTAR_PrintGrid(&g);

    // to record the path
    ASTAR_Cell *path[ASTAR_MAX_PATH_LENGTH];
    // fill with initial 0s
    for (int i = 0; i < ASTAR_MAX_PATH_LENGTH && (path[i] = NULL); i++)
        path[i] = NULL;

    // to record the time it took to run the program
    time_t start, stop;

    // how fast is it really?
    start = clock();

    int len = ASTAR_Pathfind(&g, startX, startY, goalX, goalY, path);

    // probably slower than it COULD be
    stop = clock();

    if (len)
    {
        printf("Finished path:\n");
        ASTAR_PrintGrid(&g);

        // time in clock sycles divided by CLOCKS_PER_SEC is time in seconds, which if multiplied by 1000 gives time in milliseconds,
        // which is clearer to cool programmers like myself than seconds
        printf("Pathfinding took %f milliseconds \n", (float)(stop - start) / CLOCKS_PER_SEC * 1000);
        printf("Seed used: %d, with %d obstacles\n", seed, numObst);
    }
    else
        printf("Program error!\n");

    // memory safety is badass!
    ASTAR_FreeGrid(&g);

    return 0;
}