#ifndef CELL_H
#define CELL_H

typedef struct Cell
{
    int x, y;
    // 0 for nothing, 1 for open, 2 for closed, 3 for non-traversable
    int value;
    double G, F;
    struct Cell *parent;
} Cell;

#endif