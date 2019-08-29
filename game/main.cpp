#include "game.h"

#include <sdl.h>

int main(int argc, char* args[]) {
	Game game(new Engine());

	game.Startup();

	while (!game.Quit()) {
		game.Update();
	}

	game.Shutdown();

	return 0;
}