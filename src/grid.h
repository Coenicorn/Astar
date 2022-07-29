#ifndef GRID_H
#define GRID_H

#include "cell.h"

#define V_DEFAULT 0
#define V_OPEN 1
#define V_CLOSED 2
#define V_BLOCKED 3
#define V_PATH 4

#define WALKABLE_CHANCE .2

typedef struct AstarGrid
{
    // two dimensional grid of cells
    struct AstarCell **data;
    int w, h;
    int len;
} AstarGrid;

/** Helper function to get a grid with cells with value V_DEFAULT
 * @param w The width of the grid in cells
 * @param h The height of the grid in cells
 * @returns A grid with cells with value V_DEFAULT
 * */
AstarGrid *newAstarGrid(int w, int h);

/** Get a grid of cells with randomized obstacles
 * @param w The width of the grid in cells
 * @param h The height of the grid in cells
 * @param numObstacles The number of obstacles the grid should have
 * @returns A grid filled with cells (see cell.h)
 * */
AstarGrid *newRandomAstarGrid(int w, int h, int numObstacles);

/** Frees any given grid from memory
 * @param g The grid to free
 * */
void freeGrid(AstarGrid *g);

/** Prints a grid to the console
 * @param g The grid to free to console
 * @note Watch out with grids that are bigger than console width or height, this function doesn't account for that and will thus wrap around
 * */
void printGrid(AstarGrid *g);

#endif