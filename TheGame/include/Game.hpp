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
	void SetupNewLevel();
	int SetupGameObject(std::string texture, std::string sound, uint16 physicsCategory, bool isEntity, int frames = ANIMATION_FRAMES, bool isPlayer = false);

	// Callbacks to collisions
	std::function<void(void* ptr)> m_newLevelCallback;
	std::function<void(void* ptr)> m_unlockDoorCallback;
	std::function<void(void* ptr)> m_collectScoreCallback;

	Level m_level;
	b2World m_world;
	PhysicsCollisionListener m_collisionListener;
	SFMLDebugDraw m_debugDraw;

	std::vector<std::shared_ptr<GameObject>> m_gameObjects;

	std::vector<std::shared_ptr<InputComponent>> m_inputComponents;
	std::vector<std::shared_ptr<AIComponent>> m_aiComponents;
	std::vector<std::shared_ptr<PhysicsComponent>> m_physicComponents;
	std::vector<std::shared_ptr<AnimatorComponent>> m_animatorComponents;
	std::vector<std::shared_ptr<SpriteComponent>> m_spriteComponents;
	std::vector<std::shared_ptr<HealthComponent>> m_healthComponents;
	std::vector<std::shared_ptr<SoundComponent>> m_soundComponents;

	sf::Clock m_clock;
	sf::Time m_previousTime;
	sf::Font m_font;

	int m_scoreTotal;
	bool m_generateNewLevel;
};

#endif // !GAME_HPP
