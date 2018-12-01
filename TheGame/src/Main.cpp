#include "Game.hpp"

int main(int argc, char** argv) {
	Game game;
	while (!game.IsRunning()) {
		game.Update();
		game.Render();
		game.RestartClock();
	}
	return 0;
}