/*

C implementation of the A* pathfinding algorithm.
Probably way longer than it needs to be, but frankly, I don't really care lol.

To use this implementation, define a grid (as per the ASTAR_Grid struct) and call the getPath() function with
correct arguments.

There is a path returned (an array of pointers to the cells in the grid) but I don't use it as this implementation is mostly just to look cool
and for me to feel slightly good about my programming skills (which is very illjustified lol).

If you're actually reading this, enjoy! (What are you doing tho?)

*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "astar.h"

// define to print every algorithm step to console
#define VISUALIZE

#ifdef VISUALIZE

    // define to make program run at a step-by-step fps rate
    #define VIS_STRICT

    #define VIS_STEPS_PER_FRAME 50

    #define VIS_FPS 20
    
    #define VIS_FPS_CLOCK ((float)(CLOCKS_PER_SEC) / (float)(VIS_FPS))

#endif // VISUALISE

#define WEIGHT 1

#define SQRT2 1.41421356237

const int dirsX[8] = {-1, 0, 1, 0, 1, 1, -1, -1};
const int dirsY[8] = {0, -1, 0, 1, -1, 1, -1, 1};

int MAX_OPEN_LENGTH;

#ifdef VIS_STRICT

static void sleep_clk(clock_t cycle)
{
    clock_t last = clock() + cycle, next;

    while ((next = clock()) < last)
        ;;
}

#endif // VISUALIZE

static double ASTAR_Heuristic(int dX, int dY)
{
    // return sqrt(dX * dX + dY * dY);
    return dX + dY;
}

static void ASTAR_SqueezeOpen(ASTAR_Cell *openIn[], int *len)
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
            if (openIn[i]->value == ASTAR_V_OPEN)
                openIn[j++] = openIn[i];
            else
                openIn[i] = NULL;
        }
    }

    *len = j;
}

int ASTAR_OnNeighbour(ASTAR_Grid *g, ASTAR_Cell *p, ASTAR_Cell *open[MAX_OPEN_LENGTH], int *openLength, int goalX, int goalY, int dir)
{
    int dX = dirsX[dir], dY = dirsY[dir];

    int x = p->x + dX, y = p->y + dY;

    int diagonal = !(dX == 0 || dY == 0);

    // check if neighbour position is inside grid
    if (!ASTAR_IsValidPosition(g, x, y) || g->data[y][x].value == ASTAR_V_CLOSED)
        return 0;
    
    int willPhase = (diagonal && g->data[p->y][p->x + dX].value == ASTAR_V_BLOCKED && g->data[p->y + dY][p->x].value == ASTAR_V_BLOCKED);

    if (willPhase)
        return 0;

    ASTAR_Cell *n = &g->data[y][x];

    // get new G value
    double nG = p->G + (diagonal ? SQRT2 : 1);

    if (n->value == ASTAR_V_DEFAULT || nG < n->G)
    {
        n->parent = p;
        n->G = nG;

        n->F = n->G + ASTAR_Heuristic(abs(x - goalX), abs(y - goalY)) * WEIGHT;

        n->value = ASTAR_V_OPEN;

        *openLength += 1;

        // check if the open array has overflown
        if (*openLength >= MAX_OPEN_LENGTH)
            return 1;

        open[*openLength] = n;
    }

    return 0;
}

int ASTAR_Pathfind(ASTAR_Grid *g, int startX, int startY, int goalX, int goalY, ASTAR_Cell **path_out, int *pathlength)
{
    if (path_out == NULL)
    {
        printf("**Output path isn't defined**\n");
        return 1;
    }

    // no idea if this makes it faster, but it dynamically alters
    // the max open length to match program width and height... maybe idk
    MAX_OPEN_LENGTH = g->w * g->h;

    // check if the start and end positions are valid
    if (!ASTAR_IsValidPosition(g, startX, startY))
    {
        printf("**Start position is not in grid bounds**\n");
        return 1;
    }
    if (!ASTAR_IsValidPosition(g, goalX, goalY))
    {
        printf("**Goal position is not in grid bounds**\n");
        return 1;
    }

    // set start cell to open
    ASTAR_Cell *s = &g->data[startY][startX];
    s->value = ASTAR_V_OPEN;
    s->F = ASTAR_Heuristic(abs(startX - goalX), abs(startX - goalX));
    s->G = 0;

    // initialize open array
    ASTAR_Cell *open[MAX_OPEN_LENGTH];

    for (int i = 0; i < MAX_OPEN_LENGTH; i++)
        open[i] = NULL;

    open[0] = s;

    // initialize length of open array, the first item in the array is already open, hence the value 1
    int openLength = 1;

    int pathFound = 0;

    ASTAR_Cell *current = open[0];

#ifdef VISUALIZE

    clock_t clock_next = clock();

    int iteration = 0;
    int steps = 0;

#endif // VISUALIZE
    
    // main pathfinding loop
    while (!pathFound)
    {
        // get the amount of cells in the front of the open array
        ASTAR_SqueezeOpen(open, &openLength);

        // record best F score
        double lowestF = INFINITY;

        // loop over all cells in open array
        for (int i = 0; i < openLength; i++)
        {
            ASTAR_Cell *c = open[i];

            // record best scoring cell
            if (c->value == ASTAR_V_OPEN && c->F < lowestF)
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

        current->value = ASTAR_V_CLOSED;

        // open all neighbours of the current cell
        for (int i = 0; i < 8; i++)
        {
            if (ASTAR_OnNeighbour(g, current, open, &openLength, goalX, goalY, i))
            {
                printf("**Open array overflow**\n");
                return 1;
            }
        }

        iteration++;

#ifdef VISUALIZE

        long diff = clock_next - clock();


#ifdef VIS_STRICT
        if (diff >= 0 && steps >= VIS_STEPS_PER_FRAME) 
        {
            sleep_clk(diff);
        }
#endif // VIS_STRICT

        if (clock() >= clock_next)
        {
            ASTAR_PrintGrid(g);
            printf("iteration %i\n", iteration);

            steps = 0;
            clock_next = clock() + VIS_FPS_CLOCK;
        }

        steps++;

#endif // VISUALIZE
    }

#ifdef VISUALIZE

    ASTAR_PrintGrid(g);
    printf("iteration %i\n", iteration);

#endif // VISUALIZE

    // loop exited but there's no path, no path is possible
    if (!pathFound)
    {
        printf("**No path is possible**\n");
        return 1;
    }

    // backtrack
    int i = 0;
    while (1)
    {
        current->value = ASTAR_V_PATH;
        path_out[i] = current;

        if (i >= ASTAR_MAX_PATH_LENGTH)
        {
            printf("**Path longer than ASTAR_MAX_PATH_LENGTH**\n");
            return 1;
        }

        if (!current->parent)
            break;

        i++;

        current = current->parent;
    }
    // reverse
    for (int n = 0, m = i; n < m; n++, m--)
    {
        ASTAR_Cell *t = path_out[n];
        path_out[n] = path_out[m];
        path_out[m] = t;
    }

    (*pathlength) = i + 1;

    return 0;
}