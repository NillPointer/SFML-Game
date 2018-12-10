#include "Menu.hpp"
#include "Util.hpp"

Menu::Menu(std::shared_ptr<Window> windowprt): Scene(windowprt) {
}

void Menu::Update() {
	sf::Clock deltaClock;
	m_window->Update();

	ImGui::SFML::Update(*m_window->GetRenderWindow(), deltaClock.restart());

	DisplayMainMenu();
}

void Menu::DisplayMainMenu() {
	ImVec2 size = { ImGui::GetIO().DisplaySize.x * MENU_WINDOW_WIDTH_SCALE , ImGui::GetIO().DisplaySize.y * MENU_WINDOW_HEIGHT_SCALE };
	ImGui::SetNextWindowSize(size);
	ImGui::SetNextWindowPos({ (ImGui::GetIO().DisplaySize.x / 2.0f) - size.x / 2 , (ImGui::GetIO().DisplaySize.y / 2.0f) - size.y / 2 });
	ImGui::Begin("", nullptr, MENU_WINDOW_FLAGS);
	ImGui::Indent(size.x / 2.0f - ImGui::CalcTextSize(WINDOW_TITLE).x/2.0f);
	ImGui::Text(WINDOW_TITLE);
	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::Indent(-ImGui::CalcTextSize(START_GAME).x / 2.0f -30.0f);
	if (ImGui::Button(START_GAME, { 200, 100 })) SetChangeScene(true);
	ImGui::NewLine();
	if (ImGui::Button(EXIT_GAME, { 200, 100 })) Exit();
	ImGui::End();
}

void Menu::Render() {
	m_window->BeginDraw();
	ImGui::SFML::Render(*m_window->GetRenderWindow());
	m_window->EndDraw();
}
