#include "Game.hpp"
#include <functional>
#include <SFML/Audio.hpp>
#include "AssetManager.hpp"

Game::Game(std::shared_ptr<Window> windowprt):
	Scene(windowprt),
	m_world(b2Vec2(0,0)),
	m_level(*m_window->GetRenderWindow()),
	m_generateNewLevel(true),
	m_debugDraw(*m_window->GetRenderWindow())
{
	GetBackgroundMusic().openFromFile("resource/music/msc_main_track_3.wav");
	m_font.loadFromFile("resource/fonts/ADDSBP__.TTF");

	m_world.SetContactListener(&m_collisionListener);
	m_world.SetDebugDraw(&m_debugDraw);
	m_debugDraw.SetFlags(b2Draw::e_shapeBit);

	// Setup Player
	SetupGameObject("resource/players/mage/spr_mage_", "", PLAYER, true, ANIMATION_FRAMES);
	m_gameObjects[0]->SetName(PLAYER_ENTITY);
	m_gameObjects[0]->SetAttackComponent(std::make_shared<AttackComponent>(*m_gameObjects[0], m_world, m_collisionListener));
	m_gameObjects[0]->SetInputComponent(std::make_shared<InputComponent>(*m_gameObjects[0]));
	m_attackComponents.push_back(m_gameObjects[0]->GetAttackComponent());
	m_inputComponents.push_back(m_gameObjects[0]->GetInputComponent());

	// Setup Key
	SetupGameObject("resource/loot/key/spr_pickup_key.png", "resource/sounds/snd_key_pickup.wav", DOOR_KEY, false);

	// Setup Score (Gems)
	for (int i = 0; i < 15; ++i)
		SetupGameObject("resource/loot/gem/spr_pickup_gem.png", "resource/sounds/snd_gem_pickup.wav", SCORE, false);

	// Setup Torches
	for (int i = 0; i < 5; ++i) {
		auto index = SetupGameObject("resource/spr_torch.png", "resource/sounds/snd_fire.wav", 0, false, 5);
		m_gameObjects[index]->GetSoundComponent()->SetSoundLooping(true);
		m_gameObjects[index]->SetName(TORCH);
	}

	// Setup Collision callbacks
	m_newLevelCallback = [&](GameObject *a, GameObject* b) { m_generateNewLevel = true; };
	m_unlockDoorCallback = [&](GameObject *a, GameObject *b) {
		m_level.UnlockDoor(); 
		b->GetSoundComponent()->PlaySound(); 
		b->Deactivate(); 
	};
	m_collectScoreCallback = [&](GameObject *a, GameObject* b) {
		printf("score picked up\n"); 
		b->GetSoundComponent()->PlaySound(); 
		b->Deactivate(); 
	};

	m_collisionListener.SetCollisionCallback(PLAYER | UNLOCKED_DOOR, m_newLevelCallback);
	m_collisionListener.SetCollisionCallback(PLAYER | DOOR_KEY, m_unlockDoorCallback);
	m_collisionListener.SetCollisionCallback(PLAYER | SCORE, m_collectScoreCallback);

	// Limit Framerate
	m_window->GetRenderWindow()->setFramerateLimit(FPS);
}

void Game::Initialize(bool networking, bool host, int seed) {
	m_generateNewLevel = true;
	m_clock.restart();
	m_previousTime = m_clock.getElapsedTime();
	srand(seed == -1 ? time(nullptr) : seed);

	for (auto gameObject : m_gameObjects) if (gameObject->GetNetworkComponent() != nullptr) gameObject->GetNetworkComponent().~shared_ptr();
	m_networkComponents.clear();

	if (networking) {
		if (host) {
			m_gameObjects[0]->SetNetworkComponent(std::make_shared<NetworkComponent>(*m_gameObjects[0]));
			m_networkComponents.push_back(m_gameObjects[0]->GetNetworkComponent());
			m_gameObjects[0]->GetNetworkComponent()->SetIsHost(host);
			m_gameObjects[0]->GetNetworkComponent()->Connect("172.16.128.25");
		} else {
			SetupGameObject("resource/enemies/skeleton/spr_skeleton_", "", ENEMY, true, ANIMATION_FRAMES);
			m_gameObjects[m_gameObjects.size() - 1]->SetNetworkComponent(std::make_shared<NetworkComponent>(*m_gameObjects[m_gameObjects.size() - 1]));
			m_networkComponents.push_back(m_gameObjects[m_gameObjects.size() - 1]->GetNetworkComponent());
			m_gameObjects[m_gameObjects.size() - 1]->GetNetworkComponent()->SetIsHost(host);
			m_gameObjects[m_gameObjects.size() - 1]->GetNetworkComponent()->Connect("172.16.128.25");
		}
	}

}

Game::~Game() {}

void Game::Update() {
	m_window->Update();
	sf::Time deltaTime = m_clock.getElapsedTime() - GetElapsed();
	//if (m_window->IsPaused()) return;

	if (m_generateNewLevel) SetupNewLevel();
	for (auto attack : m_attackComponents) attack->DestroyProjectiles();

	for (auto input : m_inputComponents) input->Update(deltaTime.asSeconds());
	for (auto ai : m_aiComponents) ai->Update(deltaTime.asSeconds());
	for (auto physic : m_physicComponents) physic->Update(deltaTime.asSeconds());
	for (auto network : m_networkComponents) network->Update(deltaTime.asSeconds());
	for (auto animator : m_animatorComponents) animator->Update(deltaTime.asSeconds());
	for (auto sprite : m_spriteComponents) sprite->Update(deltaTime.asSeconds());
	for (auto sound : m_soundComponents) sound->Update(deltaTime.asSeconds());
	for (auto attack : m_attackComponents) attack->Update(deltaTime.asSeconds());

	if (m_gameObjects[0]->GetPhysicsComponent() != nullptr) {
		auto playerPosition = m_gameObjects[0]->GetPhysicsComponent()->GetPosition();
		m_window->MoveView(playerPosition);
		sf::Listener::setPosition(playerPosition.x, 0.0f, playerPosition.y);
	}

	m_world.Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U)) m_level.UnlockDoor();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) m_generateNewLevel = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) SetChangeScene(true);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) for (auto sound : m_soundComponents) sound->SetActive(false);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) for (auto sound : m_soundComponents) sound->SetActive(true);
}

void Game::Render() {
	m_window->BeginDraw();

	m_window->Draw(m_level);

	for (auto sprite : m_spriteComponents) m_window->Draw(*sprite);
	for (auto attack : m_attackComponents) m_window->Draw(*attack);

	if (m_window->IsDebug()) m_world.DrawDebugData();

	m_window->EndDraw();
}

void Game::SetupNewLevel() {
	m_generateNewLevel = false;
	m_gameObjects[0]->GetPhysicsComponent()->SetPosition(m_level.GenerateLevel(m_world));
	//m_gameObjects[m_gameObjects.size() - 1]->GetPhysicsComponent()->SetPosition({ 0,0 });
	//m_gameObjects[m_gameObjects.size() - 1]->GetAIComponent()->SetLevel(&m_level);
	//m_gameObjects[m_gameObjects.size() - 1]->GetAIComponent()->SetTargetPosition(m_gameObjects[0]->GetPhysicsComponent()->GetPosition());
	for (auto i = 1; i < m_gameObjects.size(); ++i) {
		m_gameObjects[i]->Activate();
		bool torch = m_gameObjects[i]->GetName() == TORCH;
		m_gameObjects[i]->GetPhysicsComponent()->SetPosition(m_level.GetRandomSpawnLocation(torch));
	}
}

int Game::SetupGameObject(std::string texture, std::string sound, uint16 physicsCategory, bool isEntity, int frames) {
	std::shared_ptr<GameObject> object = std::make_shared<GameObject>();
	b2Body* body = isEntity ? CreateCirclePhysicsBody(m_world, { 0, 0 }, 0.5f, b2_dynamicBody) : 
		CreateSquarePhysicsBody(m_world, { 0, 0 }, { 0.45f, 0.45f }, b2_dynamicBody);
	SetPhysicsBodyFilter(body, physicsCategory, !isEntity);
	body->SetUserData(object.get());

	object->SetSpriteComponent(std::make_shared<SpriteComponent>(*object));
	object->SetAnimatorComponent(std::make_shared<AnimatorComponent>(*object));
	object->SetPhysicsComponent(std::make_shared<PhysicsComponent>(*object, body));
	if (!sound.empty()) object->SetSoundComponent(std::make_shared<SoundComponent>(*object, AssetManager::AddSoundBuffer(sound)));
	if (isEntity) object->SetHealthComponent(std::make_shared<HealthComponent>(*object));

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
	if (isEntity) m_healthComponents.push_back(object->GetHealthComponent());

	return m_gameObjects.size() - 1;
}

sf::Time Game::GetElapsed() {
	return m_clock.getElapsedTime() - m_previousTime;
}

void Game::RestartClock() {
	m_previousTime += GetElapsed();
	m_clock.restart();
}