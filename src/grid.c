#include <stdlib.h>
#include <stdio.h>

#include "astar.h"

// for visualization, corresponds to the V_* values (any ASTAR_V_DEFAULT cell will be shown as a space, 
// any ASTAR_V_OPEN cell will be shown as +, etc.)
const char output_values[5] = {' ', '+', '-', '/', '@'};

int ASTAR_IsValidPosition(ASTAR_Grid *g, int x, int y)
{
    return (x >= 0 && x < g->w && y >= 0 && y < g->h);
}

ASTAR_Grid *ASTAR_NewGrid(int w, int h)
{
    ASTAR_Grid *out = malloc(sizeof(ASTAR_Grid));

    // initialize two dimensional grid
    out->data = malloc(sizeof(ASTAR_Cell *) * h);
    for (int y = 0; y < h; y++)
    {
        out->data[y] = malloc(sizeof(ASTAR_Cell) * w);
    }

    out->w = w;
    out->h = h;

    // fill grid with default nodes
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            // is the tile traversable?

            // for completely randomized grid
            // int value = (((float)rand() / (float)RAND_MAX) < WALKABLE_CHANCE) * ASTAR_V_BLOCKED;

            int value = ASTAR_V_DEFAULT;

            out->data[y][x] = (ASTAR_Cell){x, y, value, 0.0, 0.0, NULL};
        }
    }

    return out;
}

void ASTAR_FreeGrid(ASTAR_Grid *g)
{
    for (int i = 0, l = g->h; i < l; i++)
    {
        free(g->data[i]);
    }
    free(g->data);
    free(g);
}

void ASTAR_PrintGrid(ASTAR_Grid *g)
{
    for (int y = 0; y < g->h; y++)
    {
        for (int x = 0; x < g->w; x++)
        {
            int v = g->data[y][x].value;

            putchar(output_values[v]);

            // width is smaller than height in console output
            putchar(' ');
        }
        putchar('\n');
    }
    putchar('\n');
}