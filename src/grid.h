#ifndef GRID_H
#define GRID_H

#include "cell.h"

#define V_DEFAULT 0
#define V_OPEN 1
#define V_CLOSED 2
#define V_BLOCKED 3
#define V_PATH 4

typedef struct ASTAR_Grid
{
    // two dimensional grid of cells
    struct ASTAR_Cell **data;
    int w, h;
    int len;
} ASTAR_Grid;

/** Helper function to get a grid with cells with value V_DEFAULT
 * @param w The width of the grid in cells
 * @param h The height of the grid in cells
 * @returns A grid with cells with value V_DEFAULT
 * */
ASTAR_Grid *ASTAR_NewGrid(int w, int h);

/** Frees any given grid from memory
 * @param g The grid to free
 * */
void ASTAR_FreeGrid(ASTAR_Grid *g);

/**
 * @brief Checks if position (x, y) is inside the bounds of given grid
 * 
 * @param g The grid to check
 * @param x The points' x
 * @param y The points' y
 * @return 1 for valid pos, 0 for not
 */
int ASTAR_IsValidPosition(ASTAR_Grid *g, int x, int y);

/** Prints a grid to the console
 * @param g The grid to free to console
 * @note Watch out with grids that are bigger than console width or height, this function doesn't account for that and will thus wrap around
 * */
void ASTAR_PrintGrid(ASTAR_Grid *g);

#endif