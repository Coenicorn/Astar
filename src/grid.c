#include <grid.h>
#include <stdlib.h>
#include <stdio.h>
#include <cell.h>

// for visualization, corresponds to the V_* values (any V_DEFAULT cell will be shown as a space, 
// any V_OPEN cell will be shown as +, etc.)
const char output_values[5] = {' ', '+', '-', '/', '@'};

int isValidPosition(Grid *g, int x, int y)
{
    return (x >= 0 && x < g->w && y >= 0 && y < g->h);
}

void blockPos(Grid *g, int x, int y)
{
    if (isValidPosition(g, x, y))
        g->data[y][x].value = V_BLOCKED;
}

void dotGrid(Grid *g, int x, int y)
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

Grid *getGrid(int w, int h, int numDots)
{
    Grid *out = malloc(sizeof(Grid));

    // initialize two dimensional grid
    out->data = malloc(sizeof(Cell *) * h);
    for (int y = 0; y < h; y++)
    {
        out->data[y] = malloc(sizeof(Cell) * w);
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

            out->data[y][x] = (Cell){x, y, value, 0.0, 0.0, NULL};
        }
    }

    // if ya don't want no dots, we aint givin' ya no dots!
    if (!numDots)
        return out;

    for (int i = 0; i < numDots; i++)
    {
        // random position on grid
        int x = (int)(((float)rand() / (float)RAND_MAX) * w);
        int y = (int)(((float)rand() / (float)RAND_MAX) * h);

        dotGrid(out, x, y);
    }

    return out;
}

void freeGrid(Grid *g)
{
    for (int i = 0, l = g->h; i < l; i++)
    {
        free(g->data[i]);
    }
    free(g->data);
    free(g);
}

void printGrid(Grid *g)
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