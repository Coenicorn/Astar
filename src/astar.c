/*

C implementation of the A* pathfinding algorithm.
Probably way longer than it needs to be, but frankly, I don't really care lol.

To use this implementation, define a grid (as per the AstarGrid struct) and call the getPath() function with
correct arguments.

There is a path returned (an array of pointers to the cells in the grid) but I don't use it as this implementation is mostly just to look cool
and for me to feel slightly good about my programming skills (which is very illjustified lol).

If you're actually reading this, enjoy! (What are you doing tho?)

As for other programmers reading this:

The maximum time complexity of this program is still the same as that of floodfill,
because in the worst case scenario you'll still have to traverse all the cells in the grid.
The best case scenario is quite a bit better though, as the heuristic kind of "guides" the pathfinding
towards the target as opposed to just filling everything and randomly stumbling across the
path like floodfill does.

The space complexity is pretty bad, as all the cells in the grid are stored in memory and the
open array has a fixed size. Still, a pretty cool algorithm if you'd ask me!

*/


#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "astar.h"
#include "grid.h"
#include "cell.h"

#define WEIGHT 1

#define SQRT2 1.41421356237

const int dirsX[8] = {-1, 0, 1, 0, 1, 1, -1, -1};
const int dirsY[8] = {0, -1, 0, 1, -1, 1, -1, 1};

int MAX_OPEN_LENGTH;

double heuristic(int dX, int dY)
{
    return sqrt(dX * dX + dY * dY);
    // return dX + dY;
}

void squeezeOpen(AstarCell *openIn[MAX_OPEN_LENGTH], int *len)
{
    *len += 8;

    if (*len >= MAX_OPEN_LENGTH)
        *len = MAX_OPEN_LENGTH;

    int i, j;
    for (i = j = 0; i < *len; i++)
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

    *len = j;
}

int onNeighbour(AstarGrid *g, AstarCell *p, AstarCell *open[MAX_OPEN_LENGTH], int *openLength, int goalX, int goalY, int dir)
{
    int dX = dirsX[dir], dY = dirsY[dir];

    int x = p->x + dX, y = p->y + dY;

    // check if neighbour position is inside grid
    if (!isValidPosition(g, x, y) || g->data[y][x].value == V_CLOSED)
        return 0;

    AstarCell *n = &g->data[y][x];

    // get new G value
    int isDiagonal = (dX == 0 || dY == 0);

    double nG = p->G + (isDiagonal ? 1 : SQRT2);

    if (n->value == V_DEFAULT || nG < n->G)
    {
        n->parent = p;
        n->G = nG;

        n->F = n->G + heuristic(abs(x - goalX), abs(y - goalY)) * WEIGHT;

        n->value = V_OPEN;

        *openLength += 1;

        // check if the open array has overflown
        if (*openLength >= MAX_OPEN_LENGTH)
            return 1;

        open[*openLength] = n;
    }

    return 0;
}

int pathfind(AstarGrid *g, int startX, int startY, int goalX, int goalY, AstarCell *path_out[])
{
    if (path_out == NULL)
    {
        printf("**Output path isn't defined**\n");
        return 0;
    }

    // no idea if this makes it faster, but it dynamically alters
    // the max open length to match program width and height... maybe idk
    MAX_OPEN_LENGTH = g->w * g->h;

    // check if the start and end positions are valid
    if (!isValidPosition(g, startX, startY))
    {
        printf("**Start position is not in grid bounds**\n");
        return 0;
    }
    if (!isValidPosition(g, goalX, goalY))
    {
        printf("**Goal position is not in grid bounds**\n");
        return 0;
    }

    // set start cell to open
    AstarCell *s = &g->data[startY][startY];
    s->value = V_OPEN;
    s->F = heuristic(abs(startX - goalX), abs(startX - goalX));
    s->G = 0;

    // initialize open array
    AstarCell *open[MAX_OPEN_LENGTH];

    for (int i = 0; i < MAX_OPEN_LENGTH; i++)
        open[i] = NULL;

    open[0] = s;

    // initialize length of open array, the first item in the array is already open; hence the value 1
    int openLength = 1;

    int pathFound = 0;

    AstarCell *current = open[0];

    // main pathfinding loop
    while (!pathFound)
    {
        // get the amount of cells in the front of the open array
        squeezeOpen(open, &openLength);

        // record best F score
        double lowestF = INFINITY;

        // loop over all cells in open array
        for (int i = 0; i < openLength; i++)
        {
            AstarCell *c = open[i];

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
        for (int i = 0; i < 8; i++)
        {
            if (onNeighbour(g, current, open, &openLength, goalX, goalY, i))
            {
                printf("**Open array overflow**\n");
                return 0;
            }
        }
    }

    // loop exited but there's no path, no path is possible
    if (!pathFound)
    {
        printf("**No path is possible**\n");
        return 0;
    }

    // backtrack
    int i = 0;
    while (1)
    {
        current->value = V_PATH;
        path_out[i] = current;

        if (i >= MAX_PATH_LENGTH)
        {
            printf("**Path longer than MAX_PATH_LENGTH**\n");
            return 0;
        }

        if (!current->parent)
            break;

        i++;
        current = current->parent;
    }

    return i;
}