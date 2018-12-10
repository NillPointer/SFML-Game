#include "Game.hpp"
#include <functional>
#include "TextureManager.hpp"

Game::Game(std::shared_ptr<Window> windowprt):
	Scene(windowprt), m_world(b2Vec2(0,0)),
	m_debugDraw(*m_window->GetRenderWindow())
{
	m_clock.restart();
	m_previousTime = m_clock.getElapsedTime();
	srand(time(nullptr));

	m_world.SetContactListener(&m_collisionListener);
	m_world.SetDebugDraw(&m_debugDraw);
	m_debugDraw.SetFlags(b2Draw::e_shapeBit);

	m_font.loadFromFile("resource/fonts/ADDSBP__.TTF");
	m_level = Level(*m_window->GetRenderWindow());
	sf::Vector2f playerPos = m_level.GenerateLevel(m_world);

	// Setup Player
	SetupEntity("resource/players/mage/spr_mage_", PLAYER, playerPos, true);

	// Setup Key
	SetupItem("resource/loot/key/spr_pickup_key.png", DOOR_KEY);

	m_newLevelCallback = [&]() { m_generateNewLevel = true; };
	m_unlockDoorCallbak = [&]() { m_level.UnlockDoor(); m_gameObjects[1]->Deactivate(); };
	m_collisionListener.SetCollisionCallback(PLAYER | UNLOCKED_DOOR, m_newLevelCallback);
	m_collisionListener.SetCollisionCallback(PLAYER | DOOR_KEY, m_unlockDoorCallbak);

	m_window->GetRenderWindow()->setFramerateLimit(FPS);
}

Game::~Game() {}

void Game::SetupEntity(std::string textureFilenamePrefix, uint16 physicsCategory, sf::Vector2f position ,bool isPlayer) {
	// Creating physics body and setting collision category
	std::shared_ptr<GameObject> entity = std::make_shared<GameObject>();
	b2Body* body = CreateCirclePhysicsBody(m_world, { 0, 0 }, 0.5f, b2_dynamicBody);
	b2Filter filter = body->GetFixtureList()->GetFilterData();
	filter.categoryBits = physicsCategory;
	body->GetFixtureList()->SetFilterData(filter);

	if (isPlayer) entity->SetInputComponent(std::make_shared<InputComponent>(*entity));
	// TODO: else !isPlayer SetAIComponent
	entity->SetPhysicsComponent(std::make_shared<PhysicsComponent>(*entity, body));
	entity->SetAnimatorComponent(std::make_shared<AnimatorComponent>(*entity));
	entity->SetSpriteComponent(std::make_shared<SpriteComponent>(*entity));
	entity->SetHealthComponent(std::make_shared<HealthComponent>(*entity));

	// Loading textures and creating animations
	for (int i = 0; i < static_cast<int>(ANIMATION_STATE::COUNT); ++i) {
		entity->GetAnimatorComponent()->AddAnimation(i, TextureManager::AddTexture(textureFilenamePrefix + ANIMATION_TEXTURES[i]));
		auto size = entity->GetAnimatorComponent()->GetAnimation(i).GetTexture().getSize();
		int frames = size.x / PIXEL_PER_METER;
		for (int j = 0; j < frames; ++j)
			entity->GetAnimatorComponent()->GetAnimation(i).AddFrame({ ((int)size.x / frames) * j, 0, (int)PIXEL_PER_METER, (int)PIXEL_PER_METER });
	}

	m_gameObjects.push_back(entity);
	m_physicComponents.push_back(entity->GetPhysicsComponent());
	m_animatorComponents.push_back(entity->GetAnimatorComponent());
	m_spriteComponents.push_back(entity->GetSpriteComponent());
	m_healthComponents.push_back(entity->GetHealthComponent());
	if (isPlayer) m_inputComponents.push_back(entity->GetInputComponent());
	// TODO: else !isPlayer m_aiComponents push_back entity->GetAIComponent()

	entity->GetPhysicsComponent()->SetPosition(position);
}

void Game::SetupItem(std::string textureFilename, uint16 physicsCategory) {
	std::shared_ptr<GameObject> entity = std::make_shared<GameObject>();
	b2Body* body = CreateSquarePhysicsBody(m_world, { 0, 0 }, { 0.45f, 0.45f }, b2_staticBody);
	b2Filter filter = body->GetFixtureList()->GetFilterData();
	filter.categoryBits = physicsCategory;
	body->GetFixtureList()->SetFilterData(filter);
	body->GetFixtureList()->SetSensor(true);

	entity->SetSpriteComponent(std::make_shared<SpriteComponent>(*entity));
	entity->SetPhysicsComponent(std::make_shared<PhysicsComponent>(*entity, body));

	entity->GetSpriteComponent()->SetSprite(TextureManager::AddTexture(textureFilename));
	entity->GetSpriteComponent()->SetSpriteTextureRect({ 0,0, 33, 33 }); // TODO: account for item being animated!
	entity->GetPhysicsComponent()->SetPosition({ 100, 200 }); // TODO: Give random spawn location

	m_gameObjects.push_back(entity);
	m_physicComponents.push_back(entity->GetPhysicsComponent());
	m_spriteComponents.push_back(entity->GetSpriteComponent());
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

	//m_player.Update(deltaTime.asSeconds());
	for (auto i : m_inputComponents) i->Update(deltaTime.asSeconds());
	for (auto p : m_physicComponents) p->Update(deltaTime.asSeconds());
	for (auto a : m_animatorComponents) a->Update(deltaTime.asSeconds());
	for (auto s : m_spriteComponents) s->Update(deltaTime.asSeconds());

	m_window->MoveView(m_gameObjects[0]->GetPhysicsComponent()->GetPosition());

	m_world.Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

	if (m_generateNewLevel) {
		m_generateNewLevel = false;
		m_gameObjects[1]->Activate();
		sf::Vector2f PlayerPos = m_level.GenerateLevel(m_world);
		m_gameObjects[0]->GetPhysicsComponent()->SetPosition({ PlayerPos.x, PlayerPos.y });
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U)) m_level.UnlockDoor();
}

void Game::Render() {
	m_window->BeginDraw();

	m_window->Draw(m_level);

	for (auto s : m_spriteComponents) m_window->Draw(*s);

	if (m_window->IsDebug()) m_world.DrawDebugData();

	m_window->EndDraw();
}