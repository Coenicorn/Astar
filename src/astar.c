#include <astar.h>
#include <grid.h>
#include <cell.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double heuristic(int dX, int dY)
{
    return sqrt(dX * dX + dY * dY);
    // return dX + dY;
}

int squeezeOpen(Cell *openIn[MAX_OPEN_LENGTH])
{
    int i, j;
    for (i = j = 0; i < MAX_OPEN_LENGTH; i++)
    {
        // check for existing cell and if it is open
        if (openIn[i] != NULL)
        {
            if (openIn[i]->value == V_OPEN)
                openIn[j++] = openIn[i];
            else
                openIn[i] = NULL;
        }
    }
    return j;
}

void onNeighbour(Grid *g, Cell *p, Cell *open[MAX_OPEN_LENGTH], int *openLength, int dX, int dY, int goalX, int goalY)
{
    int x = p->x + dX, y = p->y + dY;

    // check if neighbour position is inside grid
    if (!isValidPosition(g, x, y) || g->data[y][x].value == V_CLOSED)
        return;

    Cell *n = &g->data[y][x];

    // get new G value
    int isDiagonal = (dX == 0 || dY == 0);

    double nG = p->G + (isDiagonal ? 1 : SQRT2);

    if (n->value == V_DEFAULT || nG < n->G)
    {
        n->parent = p;
        n->G = nG;

        n->F = n->G + heuristic(abs(x - goalX), abs(y - goalY)) * WEIGHT;

        n->value = V_OPEN;

        open[++*openLength] = n;
    }
}

int pathfind(Grid *g, int startX, int startY, int goalX, int goalY, Cell *path_out[MAX_PATH_LENGTH])
{
    // check if the start and end positions are valid
    if (!isValidPosition(g, startX, startY) || !isValidPosition(g, goalX, goalY))
        return 1;

    // set start cell to open
    Cell *s = &g->data[startY][startY];
    s->value = V_OPEN;
    s->F = heuristic(abs(startX - goalX), abs(startX - goalX));
    s->G = 0;

    // initialize open array
    Cell *open[MAX_OPEN_LENGTH];

    for (int i = 0; i < MAX_OPEN_LENGTH; i++)
        open[i] = NULL;

    open[0] = s;

    // initialize length of open array, the first item in the array is already open; hence the value 1
    int openLength = 0;

    int pathFound = 0;

    Cell *current;

    // main pathfinding loop
    while (!pathFound)
    {
        // get the amount of cells in the front of the open array
        openLength = squeezeOpen(open);

        if (openLength >= MAX_OPEN_LENGTH-1)
            break;
        
        // record best F score
        double lowestF = INFINITY;

        // loop over all cells in open array
        for (int i = 0; i < openLength; i++)
        {
            Cell *c = open[i];

            // record best scoring cell
            if (c->value == V_OPEN && c->F < lowestF)
            {
                lowestF = c->F;
                current = c;
            }
        }

        // if path is found, success!
        if (current->x == goalX && current->y == goalY)
        {
            pathFound = 1;
            break;
        }

        // if open list is empty and no path is found, there is no possible path
        if (lowestF == INFINITY)
            break;

        current->value = V_CLOSED;

        // open all neighbours of the current cell
        onNeighbour(g, current, open, &openLength, 1, 0, goalX, goalY);
        onNeighbour(g, current, open, &openLength, -1, 0, goalX, goalY);
        onNeighbour(g, current, open, &openLength, 0, 1, goalX, goalY);
        onNeighbour(g, current, open, &openLength, 0, -1, goalX, goalY);
        onNeighbour(g, current, open, &openLength, 1, 1, goalX, goalY);
        onNeighbour(g, current, open, &openLength, -1, -1, goalX, goalY);
        onNeighbour(g, current, open, &openLength, 1, -1, goalX, goalY);
        onNeighbour(g, current, open, &openLength, -1, 1, goalX, goalY);
    }

    // loop exited but there's no path, no path is possible
    if (!pathFound)
        return 1;

    // backtrack

    // if we don't want a path
    if (path_out == NULL)
    {
        while (1)
        {
            current->value = V_PATH;

            if (!current->parent)
                break;

            current = current->parent;
        }
    }
    // if we do want a path
    else
    {
        int i = 0;
        while (1)
        {
            current->value = V_PATH;
            path_out[i] = current;

            if (!current->parent)
                break;

            current = current->parent;
        }
    }

    return 0;
}