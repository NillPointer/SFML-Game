#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Util.hpp"

class Window {
public:
	Window();
	~Window();

	void BeginDraw();
	void EndDraw();

	void Update();

	bool IsDone();
	bool IsFullscreen();
	bool IsDebug();

	sf::RenderWindow* GetRenderWindow();
	sf::Vector2u GetWindowSize();

	void ToggleFullscreen();

	void Draw(sf::Drawable& drawable);

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

