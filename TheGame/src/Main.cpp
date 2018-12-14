#include "Game.hpp"
#include "Menu.hpp"

int main(int argc, char** argv) {
	std::shared_ptr<Window> window = std::make_shared<Window>();
	ImGui::SFML::Init(*window->GetRenderWindow());
	sf::Listener::setGlobalVolume(50.0f);
	GAME_MODE mode;
	std::shared_ptr<Scene> currentScene;

	std::shared_ptr<Scene> gameScene = std::make_shared<Game>(window);
	std::shared_ptr<Scene> menuScene = std::make_shared<Menu>(window);

	currentScene = menuScene;
	currentScene->PlayBackgroundMusic();

	while (!currentScene->IsDone()) {
		currentScene->Update();
		currentScene->Render();
		currentScene->RestartClock();
		if (currentScene->IsChangeScene()) {
			currentScene->SetChangeScene(false);
			currentScene->StopBackgroundMusic();
			mode = currentScene->GetSceneData();
			currentScene = currentScene == menuScene ? gameScene : menuScene;
			auto networkGame = mode != GAME_MODE::SINGLE;
			currentScene->Initialize(networkGame, mode == GAME_MODE::MULTI_HOST ? true : false, networkGame ? 1 : -1);
			currentScene->PlayBackgroundMusic();
		}
	}

	ImGui::SFML::Shutdown();

	return 0;
}