#include "Game.hpp"
#include "Menu.hpp"

int main(int argc, char** argv) {
	std::shared_ptr<Window> window = std::make_shared<Window>();
	ImGui::SFML::Init(*window->GetRenderWindow());
	std::shared_ptr<Scene> currentScene;

	std::shared_ptr<Scene> gameScene = std::make_shared<Game>(window);
	std::shared_ptr<Scene> menuScene = std::make_shared<Menu>(window);

	currentScene = menuScene;

	while (!currentScene->IsDone()) {
		currentScene->Update();
		currentScene->Render();
		currentScene->RestartClock();
		if (currentScene->IsChangeScene()) {
			currentScene->SetChangeScene(false);
			currentScene = currentScene == menuScene ? gameScene : menuScene;
		}
	}

	ImGui::SFML::Shutdown();

	return 0;
}