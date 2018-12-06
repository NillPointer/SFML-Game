#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Util.hpp"

class Window {
public:
	Window();
	~Window();

	void BeginDraw();
	void Draw(sf::Drawable& drawable);
	void EndDraw();

	void Update();
	void MoveView(sf::Vector2f position);

	bool IsDone();
	bool IsFullscreen();
	bool IsDebug();

	sf::RenderWindow* GetRenderWindow();
	sf::Vector2u GetWindowSize();

	void ToggleFullscreen();

private:
	void Setup();
	void Create();
	void Destroy();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;

	bool m_isDone;
	bool m_isFullscreen;
	bool m_isDebug;
};

#endif // !WINDOW_HPP

