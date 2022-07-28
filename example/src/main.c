#include <astar.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <raylib.h>

#define W_WIDTH 500
#define W_HEIGHT 500

int main()
{
	srand((int)clock());

	InitWindow(W_WIDTH, W_HEIGHT, "A* in C");
	SetTargetFPS(60);

	Grid *g = getRandomGrid(50, 50, 50);
	printGrid(g);

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_ENTER))
		{
			pathfind(g, 0, 0, 49, 49, NULL);
			printGrid(g);
		}

		if (IsKeyPressed(KEY_R))
		{
			g = getRandomGrid(50, 50, 50);
			printGrid(g);
		}

		BeginDrawing();
		ClearBackground(WHITE);

		for (int y = 0; y < g->h; y++)
		{
			for (int x = 0; x < g->w; x++)
			{
				int v = g->data[y][x].value;

				Color c = WHITE;

				if (v == 1)
					c = BLUE;
				if (v == 2)
					c = RED;
				if (v == 4)
					c = GREEN;
				if (v == 3)
					c = BLACK;
			
				DrawRectangle(x * 10, y * 10, 10, 10, c);
			}
		}

		EndDrawing();
	}

	CloseWindow();

	freeGrid(g);

	return 0;
}