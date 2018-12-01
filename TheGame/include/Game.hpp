#ifndef GAME_HPP
#define GAME_HPP

#include "Util.hpp"
#include "Window.hpp"

class Game {
public:
	Game();
	~Game();

	void Update();
	void Render();

	bool IsRunning() { return m_window.IsDone(); }

	sf::Time GetElapsed();
	void RestartClock();

private:
	Window m_window;

	sf::Clock m_clock;
	sf::Time m_previousTime;

};

#endif // !GAME_HPP
