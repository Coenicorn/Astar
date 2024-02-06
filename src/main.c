#include <stdio.h>
#include <time.h>

#include "astar.h"

#define GRID_W 50
#define GRID_H 50

int main(void)
{
    printf("starting tests\n");

    ASTAR_Grid grid;
    ASTAR_InitGrid(&grid, GRID_W, GRID_H);

    grid.data[GRID_H-2][GRID_W-1].value = ASTAR_V_BLOCKED;
    grid.data[GRID_H-1][GRID_W-2].value = ASTAR_V_BLOCKED;
    grid.data[GRID_H-2][GRID_W-2].value = ASTAR_V_BLOCKED;

    printf("generated grid\n");

    ASTAR_Cell *path_out[ASTAR_MAX_PATH_LENGTH];
    int pathLength = 0;
    int fail = ASTAR_Pathfind(&grid, 0, 0, GRID_W-1, GRID_H-1, path_out, &pathLength);

    if (fail)
    {
        printf("no path possible\n");
        // ASTAR_PrintGrid(&grid);
    }
    else
    {
        printf("path found\nlength: %i\n", pathLength);
        // ASTAR_PrintGrid(&grid);
    }

    ASTAR_FreeGrid(&grid);

    return 0;
}