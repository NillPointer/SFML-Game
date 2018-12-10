#ifndef MENU_HPP
#define MENU_HPP

#include "imgui.h"
#include "imgui-SFML.h"
#include "Scene.hpp"

class Menu : public Scene {
public:
	Menu(std::shared_ptr<Window> windowprt);
	void Update();
	void Render();
	void RestartClock() {}

private:
	void DisplayMainMenu();
};

#endif // !MENU_HPP

