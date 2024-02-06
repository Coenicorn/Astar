#include <stdlib.h>
#include <stdio.h>

#include "astar.h"

// for visualization, corresponds to the V_* values (any ASTAR_V_DEFAULT cell will be shown as a space, 
// any ASTAR_V_OPEN cell will be shown as +, etc.)
const char output_values[5] = {' ', '+', '.', '#', '@'};

int ASTAR_IsValidPosition(ASTAR_Grid *g, int x, int y)
{
    return (x >= 0 && x < g->w && y >= 0 && y < g->h);
}

void ASTAR_InitGrid(ASTAR_Grid *g, int w, int h)
{
    // initialize two dimensional grid
    g->data = malloc(sizeof(ASTAR_Cell *) * h);
    for (int y = 0; y < h; y++)
    {
        g->data[y] = malloc(sizeof(ASTAR_Cell) * w);
    }

    g->w = w;
    g->h = h;

    // fill grid with default nodes
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            // is the tile traversable?

            // for completely randomized grid
            // int value = (((float)rand() / (float)RAND_MAX) < WALKABLE_CHANCE) * ASTAR_V_BLOCKED;

            int value = ASTAR_V_DEFAULT;

            g->data[y][x] = (ASTAR_Cell){x, y, value, 0.0, 0.0, NULL};
        }
    }
}

void ASTAR_FreeGrid(ASTAR_Grid *g)
{
    for (int i = 0, l = g->h; i < l; i++)
    {
        free(g->data[i]);
    }
    free(g->data);
}

void ASTAR_PrintGrid(ASTAR_Grid *g)
{
    int len = g->w * 2 * g->h + g->h + 1;
    char buf[len];
    int i = 0;

#define WRITE(_X) buf[i++] = _X;

    for (int y = 0; y < g->h; y++)
    {
        for (int x = 0; x < g->w; x++)
        {
            int v = g->data[y][x].value;

            WRITE(output_values[v]);

            // width is smaller than height in console output
            WRITE(' ');
        }
        WRITE('\n');
    }
    WRITE('\0');

    fwrite(buf, 1, len, stdout);

#undef WRITE
}