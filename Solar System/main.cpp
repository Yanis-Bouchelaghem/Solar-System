#include <iostream>
#include "Game.h"
#include "Settings.h"

int main()
{
	using namespace settings;
	Game game{ windowWidth, windowHeight, viewportX, viewportY, viewportWidth, viewportHeight, windowTitle };

	while (!game.ShouldClose())
	{
		game.Tick();
	}
	return 0;
}