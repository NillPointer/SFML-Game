#include "Game.hpp"

int main(int argc, char** argv) {
	std::shared_ptr<Window> window = std::make_shared<Window>();
	std::shared_ptr<Scene> currentScene;

	std::shared_ptr<Scene> gameScene = std::make_shared<Game>(window);

	currentScene = gameScene;

	while (!window->IsDone()) {
		currentScene->Update();
		currentScene->Render();
		currentScene->RestartClock();
	}
	return 0;
}