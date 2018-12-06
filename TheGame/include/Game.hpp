#ifndef GAME_HPP
#define GAME_HPP

#include "Util.hpp"
#include "Window.hpp"
#include "Level.hpp"
#include "Player.hpp"

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
	Level m_level;
	b2World m_world;

	Player m_player;

	sf::Clock m_clock;
	sf::Time m_previousTime;
	sf::Font m_font;

};

#endif // !GAME_HPP
