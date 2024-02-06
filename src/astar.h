#ifndef ASTAR_H
#define ASTAR_H

typedef struct ASTAR_Cell
{
    int x, y;
    // 0 for nothing, 1 for open, 2 for closed, 3 for non-traversable
    int value;
    double G, F;
    struct ASTAR_Cell *parent;
} ASTAR_Cell;

#define ASTAR_V_DEFAULT 0
#define ASTAR_V_OPEN 1
#define ASTAR_V_CLOSED 2
#define ASTAR_V_BLOCKED 3
#define ASTAR_V_PATH 4

typedef struct ASTAR_Grid
{
    // two dimensional grid of cells
    struct ASTAR_Cell **data;
    int w, h;
    int len;
} ASTAR_Grid;

/** Helper function to get a grid with cells with value ASTAR_V_DEFAULT
 * @param w The width of the grid in cells
 * @param h The height of the grid in cells
 * @returns A grid with cells with value ASTAR_V_DEFAULT
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

#define ASTAR_MAX_PATH_LENGTH 1000

/** Get a generated path from input variables
 * @param g The grid to do the pathfinding in
 * @param startX The start position x
 * @param startY The start position y
 * @param goalX The goal position x
 * @param goalY The goal position y
 * @param path_out A predefined path variable of length ASTAR_MAX_PATH_LENGTH, pass NULL if you don't want an output path
 * @returns Integer for program success: 1 for error, 0 for no errors
 * @note You can define a path with AstarCell *path[ASTAR_MAX_PATH_LENGTH] (name doesn't have to be path) and just pass it to the function like (getPath(... , path)
 * */
int ASTAR_Pathfind(ASTAR_Grid *g, int startX, int startY, int goalX, int goalY, ASTAR_Cell **path_out);

#endif