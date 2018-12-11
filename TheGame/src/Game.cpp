#include "Game.hpp"
#include <functional>
#include <SFML/Audio.hpp>
#include "AssetManager.hpp"

Game::Game(std::shared_ptr<Window> windowprt):
	Scene(windowprt), m_world(b2Vec2(0,0)), m_generateNewLevel(true),
	m_debugDraw(*m_window->GetRenderWindow())
{
	m_clock.restart();
	m_previousTime = m_clock.getElapsedTime();
	srand(time(nullptr));

	sf::Listener::setGlobalVolume(50.0f);

	m_world.SetContactListener(&m_collisionListener);
	m_world.SetDebugDraw(&m_debugDraw);
	m_debugDraw.SetFlags(b2Draw::e_shapeBit);

	m_font.loadFromFile("resource/fonts/ADDSBP__.TTF");
	m_level = Level(*m_window->GetRenderWindow());

	// Setup Player
	SetupGameObject("resource/players/mage/spr_mage_", "", PLAYER, true, ANIMATION_FRAMES, true);

	// Setup Key
	SetupGameObject("resource/loot/key/spr_pickup_key.png", "resource/sounds/snd_key_pickup.wav", DOOR_KEY, false);

	// Setup Score (Gems)
	for (int i = 0; i < 15; ++i)
		SetupGameObject("resource/loot/gem/spr_pickup_gem.png", "resource/sounds/snd_gem_pickup.wav", SCORE, false);

	// Setup Torches
	for (int i = 0; i < 5; ++i) {
		auto index = SetupGameObject("resource/spr_torch.png", "resource/sounds/snd_fire.wav", 0, false, 5);
		m_gameObjects[index]->GetSoundComponent()->SetSoundLooping(true);
		m_gameObjects[index]->SetName(std::string(TORCH));
	}

	// Setup Collision callbacks
	m_newLevelCallback = [&](void *ptr) { m_generateNewLevel = true; };
	m_unlockDoorCallback = [&](void *ptr) { m_level.UnlockDoor(); m_gameObjects[(int)ptr]->GetSoundComponent()->PlaySound(); m_gameObjects[(int)ptr]->Deactivate(); };
	m_collectScoreCallback = [&](void *ptr) { printf("score picked up\n"); m_gameObjects[(int)ptr]->GetSoundComponent()->PlaySound(); m_gameObjects[(int)ptr]->Deactivate(); };

	m_collisionListener.SetCollisionCallback(PLAYER | UNLOCKED_DOOR, m_newLevelCallback);
	m_collisionListener.SetCollisionCallback(PLAYER | DOOR_KEY, m_unlockDoorCallback);
	m_collisionListener.SetCollisionCallback(PLAYER | SCORE, m_collectScoreCallback);

	// Limit Framerate
	m_window->GetRenderWindow()->setFramerateLimit(FPS);
}

Game::~Game() {}

void Game::SetupNewLevel() {
	m_generateNewLevel = false;
	m_gameObjects[0]->GetPhysicsComponent()->SetPosition(m_level.GenerateLevel(m_world));
	for (auto i = 1; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->Activate();
		bool torch = m_gameObjects[i]->GetName() == std::string(TORCH);
		m_gameObjects[i]->GetPhysicsComponent()->SetPosition(m_level.GetRandomSpawnLocation(torch));
	}
}

int Game::SetupGameObject(std::string texture, std::string sound, uint16 physicsCategory, bool isEntity, int frames, bool isPlayer) {
	std::shared_ptr<GameObject> object = std::make_shared<GameObject>();
	b2Body* body = isEntity ? CreateCirclePhysicsBody(m_world, { 0, 0 }, 0.5f, b2_dynamicBody) : 
		CreateSquarePhysicsBody(m_world, { 0, 0 }, { 0.45f, 0.45f }, b2_dynamicBody);
	b2Filter filter = body->GetFixtureList()->GetFilterData();
	filter.categoryBits = physicsCategory;
	body->GetFixtureList()->SetFilterData(filter);
	body->GetFixtureList()->SetSensor(!isEntity);
	body->SetUserData((void *)m_gameObjects.size());

	object->SetSpriteComponent(std::make_shared<SpriteComponent>(*object));
	object->SetAnimatorComponent(std::make_shared<AnimatorComponent>(*object));
	object->SetPhysicsComponent(std::make_shared<PhysicsComponent>(*object, body));
	if (!sound.empty()) object->SetSoundComponent(std::make_shared<SoundComponent>(*object, AssetManager::AddSoundBuffer(sound)));
	if (isEntity) {
		object->SetHealthComponent(std::make_shared<HealthComponent>(*object));
		if (isPlayer) object->SetInputComponent(std::make_shared<InputComponent>(*object));
		// TODO: else !isPlayer SetAIComponent
	}

	for (int i = 0; i < (isEntity ? static_cast<int>(ANIMATION_STATE::COUNT) : 1); ++i) {
		std::string texturePath = isEntity ? texture + ANIMATION_TEXTURES[i] : texture;
		object->GetAnimatorComponent()->AddAnimation(i, AssetManager::AddTexture(texturePath));
		auto size = object->GetAnimatorComponent()->GetAnimation(i).GetTexture().getSize();
		auto n = size.x > PIXEL_PER_METER ? frames : 1;
		for (int j = 0; j < n; ++j)
			object->GetAnimatorComponent()->GetAnimation(i).AddFrame({ ((int)size.x / n) * j, 0, (int)size.x / n, (int)size.y });
	}

	m_gameObjects.push_back(object);
	m_physicComponents.push_back(object->GetPhysicsComponent());
	m_animatorComponents.push_back(object->GetAnimatorComponent());
	m_spriteComponents.push_back(object->GetSpriteComponent());
	if (!sound.empty()) m_soundComponents.push_back(object->GetSoundComponent());
	if (isEntity) {
		m_healthComponents.push_back(object->GetHealthComponent());
		if (isPlayer) m_inputComponents.push_back(object->GetInputComponent());
		// TODO: else !isPlayer m_aiComponents push_back entity->GetAIComponent()
	}

	return m_gameObjects.size() - 1;
}

sf::Time Game::GetElapsed() {
	return m_clock.getElapsedTime() - m_previousTime;
}

void Game::RestartClock() {
	m_previousTime += GetElapsed();
	m_clock.restart();
}

void Game::Update() {
	m_window->Update();
	sf::Time deltaTime = m_clock.getElapsedTime() - GetElapsed();

	if (m_generateNewLevel) SetupNewLevel();

	for (auto input : m_inputComponents) input->Update(deltaTime.asSeconds());
	for (auto physic : m_physicComponents) physic->Update(deltaTime.asSeconds());
	for (auto animator : m_animatorComponents) animator->Update(deltaTime.asSeconds());
	for (auto sprite : m_spriteComponents) sprite->Update(deltaTime.asSeconds());
	for (auto sound : m_soundComponents) sound->Update(deltaTime.asSeconds());

	auto playerPosition = m_gameObjects[0]->GetPhysicsComponent()->GetPosition();
	m_window->MoveView(playerPosition);
	sf::Listener::setPosition(playerPosition.x, 0.0f, playerPosition.y);

	m_world.Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U)) m_level.UnlockDoor();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) m_generateNewLevel = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) SetChangeScene(true);
}

void Game::Render() {
	m_window->BeginDraw();

	m_window->Draw(m_level);

	for (auto sprite : m_spriteComponents) m_window->Draw(*sprite);

	if (m_window->IsDebug()) m_world.DrawDebugData();

	m_window->EndDraw();
}