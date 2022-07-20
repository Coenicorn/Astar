#ifndef GRID_H
#define GRID_H

#include <cell.h>

#define V_DEFAULT 0
#define V_OPEN 1
#define V_CLOSED 2
#define V_BLOCKED 3
#define V_PATH 4

#define WALKABLE_CHANCE .2

typedef struct Grid
{
    // two dimensional grid of cells
    struct Cell **data;
    int w, h;
    int len;
} Grid;

/** Get a grid of cells
 * @param w The width of the grid in cells
 * @param h The height of the grid in cells
 * @param numDots The number of dots the grid should have
 * @returns A grid filled with cells (see cell.h)
 * */
Grid *getGrid(int w, int h, int numDots);

/** Frees any given grid from memory
 * @param g The grid to free
 * */
void freeGrid(Grid *g);

/** Prints a grid to the console
 * @param g The grid to free to console
 * @note Watch out with grids that are bigger than console width or height, this function doesn't account for that and will thus wrap around
 * */
void printGrid(Grid *g);

/** Check if the given position lies within the boundaries of a given grid
 * @param g Grid to check
 * @param x Position x
 * @param y Position y
 * @returns Boolean with value 1 for valid, 0 for not valid
 * */
int isValidPosition(Grid *g, int x, int y);

#endif