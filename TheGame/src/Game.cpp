#include "Game.hpp"
#include <functional>
#include <SFML/Audio.hpp>
#include "AssetManager.hpp"

Game::Game(std::shared_ptr<Window> windowprt):
	Scene(windowprt),
	m_world(b2Vec2(0,0)),
	m_level(*m_window->GetRenderWindow()),
	m_generateNewLevel(true),
	m_networking(false),
	m_debugDraw(*m_window->GetRenderWindow())
{
	GetBackgroundMusic().openFromFile("resource/music/msc_main_track_3.wav");
	m_font.loadFromFile("resource/fonts/ADDSBP__.TTF");

	m_world.SetContactListener(&m_collisionListener);
	m_world.SetDebugDraw(&m_debugDraw);
	m_debugDraw.SetFlags(b2Draw::e_shapeBit);

	m_clientSocket.setBlocking(true);
	m_hostSocket.setBlocking(true);

	// Setup Player
	m_player = SetupGameObject("resource/players/mage/spr_mage_", "", PLAYER, true, ANIMATION_FRAMES);
	m_player->SetName(PLAYER_ENTITY);
	m_player->SetAttackComponent(std::make_shared<AttackComponent>(*m_player, m_world, m_collisionListener));
	m_player->SetInputComponent(std::make_shared<InputComponent>(*m_player));
	m_player->SetNetworkComponent(std::make_shared<NetworkComponent>(*m_player));
	m_player->GetNetworkComponent()->SetActive(false);
	m_attackComponents.push_back(m_player->GetAttackComponent());
	m_inputComponents.push_back(m_player->GetInputComponent());
	m_networkComponents.push_back(m_player->GetNetworkComponent());

	// Setup Network Player
	m_networkPlayer = SetupGameObject("resource/players/thief/spr_thief_", "", NETWORK, true, ANIMATION_FRAMES);
	m_networkPlayer->SetName(NETWORK_PLAYER);
	m_networkPlayer->SetNetworkComponent(std::make_shared<NetworkComponent>(*m_networkPlayer));
	m_networkPlayer->GetNetworkComponent()->SetActive(false);
	m_networkPlayer->GetSpriteComponent()->GetSprite()->setColor(sf::Color(255, 255, 255, 100));
	m_networkComponents.push_back(m_networkPlayer->GetNetworkComponent());
	m_networkPlayer->GetPhysicsComponent()->GetBody()->GetFixtureList()->SetSensor(true);

	// Setup Key
	SetupGameObject("resource/loot/key/spr_pickup_key.png", "resource/sounds/snd_key_pickup.wav", DOOR_KEY, false);

	// Setup Score (Gems)
	for (int i = 0; i < 15; ++i)
		SetupGameObject("resource/loot/gem/spr_pickup_gem.png", "resource/sounds/snd_gem_pickup.wav", SCORE, false);

	// Setup Torches
	for (int i = 0; i < 5; ++i) {
		auto object = SetupGameObject("resource/spr_torch.png", "resource/sounds/snd_fire.wav", 0, false, 5);
		object->GetSoundComponent()->SetSoundLooping(true);
		object->SetName(TORCH);
	}

	// Setup Enemies
	for (int i = 0; i < 0; ++i) {
		auto enemy = SetupGameObject("resource/enemies/goblin/spr_goblin_", "", ENEMY, true, ANIMATION_FRAMES);
		enemy->SetAIComponent(std::make_shared<AIComponent>(*enemy));
		enemy->GetAIComponent()->SetLevel(&m_level);
		m_aiComponents.push_back(enemy->GetAIComponent());
		enemy->SetName(ENEMY_ENTITY);
	}

	// Setup Collision callbacks
	m_newLevelCallback = [&](GameObject *a, GameObject* b) { m_generateNewLevel = true; };
	m_unlockDoorCallback = [&](GameObject *a, GameObject *b) {
		m_level.UnlockDoor(); 
		b->GetSoundComponent()->PlaySound(); 
		b->Deactivate(); 
	};
	m_collectScoreCallback = [&](GameObject *a, GameObject* b) {
		m_scoreTotal++;
		b->GetSoundComponent()->PlaySound(); 
		b->Deactivate(); 
	};
	m_damagePlayerCallback = [&](GameObject* player, GameObject* enemy) {
		if (player->GetHealthComponent() != nullptr) player->GetHealthComponent()->Damage(10);
	};

	m_collisionListener.SetCollisionCallback(PLAYER | UNLOCKED_DOOR, m_newLevelCallback);
	m_collisionListener.SetCollisionCallback(PLAYER | DOOR_KEY, m_unlockDoorCallback);
	m_collisionListener.SetCollisionCallback(PLAYER | SCORE, m_collectScoreCallback);
	m_collisionListener.SetCollisionCallback(PLAYER | ENEMY, m_damagePlayerCallback);

	// Limit Framerate
	m_window->GetRenderWindow()->setFramerateLimit(FPS);
}

void Game::Initialize(sf::IpAddress ip, bool networking, bool host) {
	m_clientSocket.disconnect();
	m_hostSocket.disconnect();
	m_player->GetNetworkComponent()->SetActive(false);
	m_networkPlayer->Deactivate();

	m_generateNewLevel = true;
	m_networking = networking;
	m_clock.restart();
	m_previousTime = m_clock.getElapsedTime();
	srand(static_cast<int>(time(nullptr)));

	if (networking) {
		if (host) {
			if (m_hostListener.listen(PORT_NUMBER) != sf::Socket::Done) return;
			if (m_hostListener.accept(m_hostSocket) != sf::Socket::Done) return;
			if (m_clientListener.listen(PORT_NUMBER+1) != sf::Socket::Done) return;
			if (m_clientListener.accept(m_clientSocket) != sf::Socket::Done) return;

			m_player->GetNetworkComponent()->SetSocket(m_hostSocket);
			m_player->GetNetworkComponent()->SetIsReceiver(false);
			m_player->GetNetworkComponent()->SetActive(true);

			m_networkPlayer->GetNetworkComponent()->SetSocket(m_clientSocket);
			m_networkPlayer->GetNetworkComponent()->SetIsReceiver(true);
			m_networkPlayer->Activate();
			srand(static_cast<int>(time(nullptr)));
		} else {
			if (m_hostSocket.connect(ip, PORT_NUMBER) != sf::Socket::Done) return;
			if (m_clientSocket.connect(ip, PORT_NUMBER+1) != sf::Socket::Done) return;

			m_player->GetNetworkComponent()->SetSocket(m_clientSocket);
			m_player->GetNetworkComponent()->SetIsReceiver(false);
			m_player->GetNetworkComponent()->SetActive(true);

			m_networkPlayer->GetNetworkComponent()->SetSocket(m_hostSocket);
			m_networkPlayer->GetNetworkComponent()->SetIsReceiver(true);
			m_networkPlayer->Activate();
			srand(static_cast<int>(time(nullptr))+1);
		}
	}

}

Game::~Game() {}

void Game::Update() {
	m_window->Update();
	sf::Time deltaTime = m_clock.getElapsedTime() - GetElapsed();

	if (m_generateNewLevel) SetupNewLevel();
	for (auto attack : m_attackComponents) attack->DestroyProjectiles();

	for (auto input : m_inputComponents) input->Update(deltaTime.asSeconds());
	for (auto ai : m_aiComponents) ai->Update(deltaTime.asSeconds());
	for (auto network : m_networkComponents) network->Update(deltaTime.asSeconds());
	for (auto physic : m_physicComponents) physic->Update(deltaTime.asSeconds());
	for (auto animator : m_animatorComponents) animator->Update(deltaTime.asSeconds());
	for (auto sprite : m_spriteComponents) sprite->Update(deltaTime.asSeconds());
	for (auto sound : m_soundComponents) sound->Update(deltaTime.asSeconds());
	for (auto attack : m_attackComponents) attack->Update(deltaTime.asSeconds());
	for (auto health : m_healthComponents) health->Update(deltaTime.asSeconds());

	if (m_player->GetPhysicsComponent() != nullptr) {
		auto playerPosition = m_player->GetPhysicsComponent()->GetPosition();
		m_window->MoveView(playerPosition);
		sf::Listener::setPosition(playerPosition.x, 0.0f, playerPosition.y);

		for (auto enemy : m_gameObjects) {
			if (enemy->GetName() == ENEMY_ENTITY) {
				auto enemyPosition = enemy->GetPhysicsComponent()->GetPosition();
				if (Distance(playerPosition, enemyPosition) < PIXEL_PER_METER * 5) enemy->GetAIComponent()->SetTarget(m_player);
			}
		}
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
	auto entrancePosition = m_level.GenerateLevel(m_world);
	m_player->GetPhysicsComponent()->SetPosition(entrancePosition);
	
	for (auto i = 1; i < m_gameObjects.size(); ++i) {
		if (m_gameObjects[i]->GetName() != NETWORK_PLAYER) m_gameObjects[i]->Activate();
		bool torch = m_gameObjects[i]->GetName() == TORCH;
		m_gameObjects[i]->GetPhysicsComponent()->SetPosition(m_level.GetRandomSpawnLocation(torch));
	}
}

std::shared_ptr<GameObject> Game::SetupGameObject(std::string texture, std::string sound, uint16 physicsCategory, bool isEntity, int frames) {
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

	return object;
}

sf::Time Game::GetElapsed() {
	return m_clock.getElapsedTime() - m_previousTime;
}

void Game::RestartClock() {
	m_previousTime += GetElapsed();
	m_clock.restart();
}