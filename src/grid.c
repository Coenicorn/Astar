#include <stdlib.h>
#include <stdio.h>

#include "cell.h"
#include "grid.h"

// for visualization, corresponds to the V_* values (any V_DEFAULT cell will be shown as a space, 
// any V_OPEN cell will be shown as +, etc.)
const char output_values[5] = {' ', '+', '-', '/', '@'};

static int isValidPosition(AstarGrid *g, int x, int y)
{
    return (x >= 0 && x < g->w && y >= 0 && y < g->h);
}

static void blockPos(AstarGrid *g, int x, int y)
{
    if (isValidPosition(g, x, y))
        g->data[y][x].value = V_BLOCKED;
}

static void dotGrid(AstarGrid *g, int x, int y)
{
    // Hardcoding go brrrrrrrrr
    blockPos(g, x, y);
    blockPos(g, x + 1, y);
    blockPos(g, x - 1, y);
    blockPos(g, x, y + 1);
    blockPos(g, x, y - 1);
    blockPos(g, x - 1, y - 1);
    blockPos(g, x + 1, y + 1);
    blockPos(g, x - 1, y + 1);
    blockPos(g, x + 1, y - 1);
    blockPos(g, x + 2, y);
    blockPos(g, x - 2, y);
    blockPos(g, x, y + 2);
    blockPos(g, x, y - 2);
}

AstarGrid *newAstarGrid(int w, int h)
{
    AstarGrid *out = malloc(sizeof(AstarGrid));

    // initialize two dimensional grid
    out->data = malloc(sizeof(AstarCell *) * h);
    for (int y = 0; y < h; y++)
    {
        out->data[y] = malloc(sizeof(AstarCell) * w);
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
            // int value = (((float)rand() / (float)RAND_MAX) < WALKABLE_CHANCE) * V_BLOCKED;

            int value = V_DEFAULT;

            out->data[y][x] = (AstarCell){x, y, value, 0.0, 0.0, NULL};
        }
    }

    return out;
}

AstarGrid *newRandomAstarGrid(int w, int h, int numObstacles)
{
    AstarGrid *out = newAstarGrid(w, h);

    // if ya don't want no dots, we aint givin' ya no dots!
    if (!numObstacles)
        return out;

    for (int i = 0; i < numObstacles; i++)
    {
        // random position on grid
        int x = (int)(((float)rand() / (float)RAND_MAX) * w);
        int y = (int)(((float)rand() / (float)RAND_MAX) * h);

        dotGrid(out, x, y);
    }

    return out;
}

void freeGrid(AstarGrid *g)
{
    for (int i = 0, l = g->h; i < l; i++)
    {
        free(g->data[i]);
    }
    free(g->data);
    free(g);
}

void printGrid(AstarGrid *g)
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