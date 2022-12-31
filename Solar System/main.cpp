#include <iostream>
#include "Game.h"

int main()
{
	Game game{ 800, 600, "Solar system"};
	while (!game.ShouldClose())
	{
		game.Tick();
	}
	return 0;
}