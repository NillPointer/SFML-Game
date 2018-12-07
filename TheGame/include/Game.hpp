#ifndef GAME_HPP
#define GAME_HPP

#include "Scene.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "SFMLDebugDraw.hpp"

class Game: public Scene {
public:
	Game(std::shared_ptr<Window> windowprt);
	~Game();

	virtual void Update();
	virtual void Render();
	virtual void RestartClock();

	sf::Time GetElapsed();

private:
	Level m_level;
	b2World m_world;
	SFMLDebugDraw m_debugDraw;

	Player m_player;

	sf::Clock m_clock;
	sf::Time m_previousTime;
	sf::Font m_font;
};

#endif // !GAME_HPP
