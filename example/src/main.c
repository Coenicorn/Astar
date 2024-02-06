#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#include "astar.h"

#define GRID_W 100
#define GRID_H 100

#define STRIKE_MAX_DEPTH 3
#define STRIKE_RANGE 8
#define STRIKE_CHILDREN 2

#define N_STRIKES 20

int randi(int min, int max)
{
    return min + (rand() % (max - min));
}

/* returns true if line goes off screen */
int astar_line(ASTAR_Grid *g, int x0, int y0, int x1, int y1)
{
    /* https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm */
    // absolutely no idea how this works, but I'm too lazy to figure it out

    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;

    while (1)
    {
        if (ASTAR_IsValidPosition(g, x0, y0))
        {
            g->data[y0][x0].value = ASTAR_V_BLOCKED;
        } else 
        {
            return 1;
        }

        if (x0 == x1 && y0 == y1) return 0;

        int e2 = 2 * error;

        if (e2 >= dy)
        {
            if (x0 == x1) return 0;

            error += dy;

            x0 += sx;
        }

        if (e2 <= dx)
        {
            if (y0 == y1) return 0;

            error += dx;

            y0 += sy;
        }
    }
}

void _strike(ASTAR_Grid *g, int x0, int y0, int x1, int y1, int depth)
{
    if (astar_line(g, x0, y0, x1, y1) || depth >= STRIKE_MAX_DEPTH || !ASTAR_IsValidPosition(g, x0, y0)) return;
    
    for (int i = 0; i < STRIKE_CHILDREN; i++)
        _strike(g, x1, y1, x1 + randi(-STRIKE_RANGE, STRIKE_RANGE), y1 + randi(-STRIKE_RANGE, STRIKE_RANGE), depth+1);
}

void strike(ASTAR_Grid *g, int x, int y)
{
    if (!ASTAR_IsValidPosition(g, x, y)) return;

    _strike(g, x, y, x, y, 0);
}

/* c in clock cycles */
static void sleep(int c)
{
    clock_t n = clock() + c;
    while (clock() < n)
        ;;
}

int main(void)
{
    srand(clock());

    while (1)
    {
        ASTAR_Grid grid;
        ASTAR_InitGrid(&grid, GRID_W, GRID_H);

        ASTAR_PrintGrid(&grid);
        for (int i = 0; i < N_STRIKES; i++)
        {
            strike(&grid, randi(0, GRID_W), randi(0, GRID_H));
            ASTAR_PrintGrid(&grid);
            sleep(CLOCKS_PER_SEC / 20);
        }

        ASTAR_PrintGrid(&grid);

        ASTAR_Cell *path_out[ASTAR_MAX_PATH_LENGTH];
        int pathLength = 0;
        int fail = ASTAR_Pathfind(&grid, 0, 0, GRID_W-1, GRID_H-1, path_out, &pathLength);

        if (fail)
        {
            printf("no path possible\n");
        }
        else
        {
            ASTAR_PrintGrid(&grid);
            printf("path found\nlength: %i\n", pathLength);
        }

        ASTAR_FreeGrid(&grid);

        sleep(CLOCKS_PER_SEC*2);
    }

    return 0;
}