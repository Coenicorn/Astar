#include <astar.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main()
{
	const int w = 40, h = 40, num_obst = 10;

	// **IMPORTANT**
	srand(time(NULL));

	Grid *g = getRandomGrid(w, h, num_obst);

	// completely optional
	printGrid(g);

	int fail = pathfind(g, 0, 0, w-1, h-1, NULL);

	// completely optional
	if (!fail)
		printGrid(g);
	
	// **VERY IMPORTANT** Always free the grid
	freeGrid(g);

	return 0;
}
