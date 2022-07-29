#include <raylib.h>
#include <astar.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define W_WIDTH 500
#define W_HEIGHT 500

int G_WIDTH, G_HEIGHT;

#define RES 20

typedef struct Cell
{
    Vector2 pos;
    int v;
} Cell;

typedef struct Player
{
    Vector2 pos;
    Vector2 velocity;
    Vector2 path[MAX_PATH_LENGTH];
    int pathlength, currentgoal;
} Player;

ASTAR_Grid *getPathGrid(Cell **grid)
{
    ASTAR_Grid *out = newAstarGrid(G_WIDTH, G_HEIGHT);

    for (int y = 0; y < G_HEIGHT; y++)
    {
        for (int x = 0; x < G_WIDTH; x++)
        {
            out->data[y][x].value = grid[y][x].v == 1 ? 3 : 0;
        }
    }

    return out;
}

void getNewPath(Player *p, Cell **grid)
{
    Vector2 mousepos = GetMousePosition();
    int x = round(mousepos.x / RES - .5), y = round(mousepos.y / RES - .5);
    if (x >= G_WIDTH)
        x = G_WIDTH-1;
    if (y >= G_HEIGHT)
        x = G_HEIGHT-1;
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;

    ASTAR_Grid *pg = getPathGrid(grid);

    ASTAR_Cell *path[MAX_PATH_LENGTH];

    p->pathlength = pathfind(pg, (int)(p->pos.x), (int)(p->pos.y), x, y, path);

    // parse path to form Vector2[]
    for (int i = 0; i < p->pathlength; i++)
    {
        p->path[i] = (Vector2){path[i]->x, path[i]->y};
    }

    freeGrid(pg);

    p->currentgoal = 1;
}

void updatePlayer(Player *p)
{
    if (!(p->currentgoal < p->pathlength))
    {
        p->pathlength = 0;
        return;
    }

    // get direction to goal
    float dX, dY;
    Vector2 target = p->path[p->currentgoal];

    dX = target.x - (p->pos.x -.5);
    dY = target.y - (p->pos.y -.5);

    // normalize
    float m = sqrt(dX * dX + dY * dY);
    dX /= m / m;
    dY /= m / m;

    if (m < .5)
    {
        p->currentgoal++;
        return;
    }

    p->pos.x += dX;
    p->pos.y += dY;
}

int main()
{
    srand(clock());

    G_WIDTH = (int)(W_WIDTH/RES)+1;
    G_HEIGHT = (int)(W_HEIGHT/RES)+1;

    // initialize grid
    Cell **grid = malloc(sizeof(Cell *) * G_HEIGHT);
    for (int i = 0; i < G_HEIGHT; i++)
    {
        grid[i] = calloc(G_WIDTH, sizeof(Cell));
        for (int j = 0; j < G_WIDTH; j++)
        {
            grid[i][j] = (Cell){
                (Vector2){j, i},
                0
            };
        }
    }

    Player player = {
        (Vector2){(int)(W_WIDTH/RES/2), (int)(W_HEIGHT/RES/2)},
        (Vector2){0, 0},
        {},
        0
    };

    InitWindow(W_WIDTH, W_HEIGHT, "A* Mouse pathing");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            getNewPath(&player, grid);
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            Vector2 mp = GetMousePosition();

            grid[(int)(mp.y/RES)][(int)(mp.x/RES)].v = 1;
        }
        if (IsKeyPressed(KEY_R))
        {
            // reset grid
            for (int i = 0; i < G_HEIGHT; i++)
                for (int j = 0; j < G_WIDTH; j++)
                    grid[i][j].v = 0;
        }


        if (player.pathlength)
            updatePlayer(&player);

        BeginDrawing();
        ClearBackground(WHITE);

        for (int i = 0; i < G_HEIGHT; i++)
        {
            DrawLine(0, i * RES, G_WIDTH * RES, i * RES, BLACK);
            for (int j = 0; j < G_WIDTH; j++)
            {
                DrawLine(j * RES, 0, j * RES, G_HEIGHT * RES, BLACK);
                if (grid[i][j].v == 1) 
                    DrawRectangle(j * RES, i * RES, RES, RES, BLACK);
            }
        }

        for (int i = 1; i < player.pathlength; i++)
        {
            Vector2 l = player.path[i-1];
            Vector2 c = player.path[i];
            DrawLineEx((Vector2){l.x * RES + RES/2, l.y * RES + RES/2}, (Vector2){c.x * RES + RES/2, c.y * RES + RES/2}, 2, GREEN);
        }

        DrawRectangle(player.pos.x * RES-5, player.pos.y * RES-5, 10, 10, RED);
        DrawText("Leftclick to path, rightclick to build obstacle, R to reset");

        EndDrawing();
    }

    CloseWindow();

    for (int i = 0; i < G_HEIGHT; i++)
    {
        free(grid[i]);
    }
    free(grid);

    return 0;
}