#ifndef ASTAR_H
#define ASTAR_H

#define MAX_PATH_LENGTH 1000
typedef struct AstarCell
{
    int x, y;
    // 0 for nothing, 1 for open, 2 for closed, 3 for non-traversable
    int value;
    double G, F;
    struct AstarCell *parent;
} AstarCell;

/* Pathfinding grid, holds grid data in twodimensional array where rows come before columns (...->data[y][x] as opposed to ...->data[x][y]) */
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

/** Get a generated path from input variables
 * @param g The grid to do the pathfinding in; THIS GRID GETS MODIFIED
 * @param startX The start position x
 * @param startY The start position y
 * @param goalX The goal position x
 * @param goalY The goal position y
 * @param path_out A predefined path variable of length MAX_PATH_LENGTH, pass NULL if you don't want an output path
 * @returns Length of path; 0 for error
 * */
int pathfind(AstarGrid *g, int startX, int startY, int goalX, int goalY, AstarCell *path_out[MAX_PATH_LENGTH]);

#endif
