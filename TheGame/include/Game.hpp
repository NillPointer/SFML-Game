#ifndef GAME_HPP
#define GAME_HPP

#include <functional>
#include "Scene.hpp"
#include "Level.hpp"
#include "PhysicsCollisionListener.hpp"
#include "SFMLDebugDraw.hpp"
#include "GameObject.hpp"

class Game: public Scene {
public:
	Game(std::shared_ptr<Window> windowprt);
	~Game();

	virtual void Update();
	virtual void Render();
	virtual void RestartClock();

	sf::Time GetElapsed();

private:
	void SetupEntity(std::string textureFilenamePrefix, uint16 physicsCategory, sf::Vector2f position, bool isPlayer = false);
	void SetupItem(std::string textureFilename, sf::Vector2f position, uint16 physicsCategory);


	std::function<void()> m_newLevelCallback;
	std::function<void()> m_unlockDoorCallbak;
	bool m_generateNewLevel = false;

	Level m_level;
	b2World m_world;
	PhysicsCollisionListener m_collisionListener;
	SFMLDebugDraw m_debugDraw;

	std::vector<std::shared_ptr<GameObject>> m_gameObjects;

	std::vector<std::shared_ptr<InputComponent>> m_inputComponents;
	std::vector<std::shared_ptr<PhysicsComponent>> m_physicComponents;
	std::vector<std::shared_ptr<AnimatorComponent>> m_animatorComponents;
	std::vector<std::shared_ptr<SpriteComponent>> m_spriteComponents;
	std::vector<std::shared_ptr<HealthComponent>> m_healthComponents;

	sf::Clock m_clock;
	sf::Time m_previousTime;
	sf::Font m_font;
};

#endif // !GAME_HPP
