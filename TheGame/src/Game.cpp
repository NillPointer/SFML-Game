#include "Game.hpp"
#include <functional>
#include "TextureManager.hpp"

Game::Game(std::shared_ptr<Window> windowprt):
	Scene(windowprt), m_world(b2Vec2(0,0)),
	m_player(m_world),
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

	m_newLevelCallback = [&]() { m_generateNewLevel = true; };
	m_unlockDoorCallbak = [&]() { m_level.UnlockDoor(); m_key.GetSpriteComponent()->GetSprite()->setColor(sf::Color::Transparent); };
	m_collisionListener.SetCollisionCallback(PLAYER | UNLOCKED_DOOR, m_newLevelCallback);
	m_collisionListener.SetCollisionCallback(PLAYER | DOOR_KEY, m_unlockDoorCallbak);

	m_player.GetPhysicsComponent()->SetPosition({ playerPos.x, playerPos.y });
	m_window->GetRenderWindow()->setFramerateLimit(FPS);

	SetupKey();
}

Game::~Game() {}

void Game::SetupKey() {
	m_key.SetSpriteComponent(std::make_shared<SpriteComponent>(m_key));
	b2Body* body = CreatePhysicsBody(m_world, { 0, 0 }, { 0.45f, 0.45f }, b2_staticBody);
	b2Filter filter = body->GetFixtureList()->GetFilterData();
	filter.categoryBits = DOOR_KEY;
	body->GetFixtureList()->SetFilterData(filter);
	body->GetFixtureList()->SetSensor(true);
	m_key.SetPhysicsComponent(std::make_shared<PhysicsComponent>(m_key, m_world, body));
	m_key.GetSpriteComponent()->SetSprite(TextureManager::AddTexture("resource/loot/key/spr_pickup_key.png"));
	m_key.GetSpriteComponent()->SetSpriteTextureRect({ 0,0, 33, 33 });
	m_key.GetPhysicsComponent()->SetPosition({ 100, 200 });
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

	m_player.Update(deltaTime.asSeconds());
	m_window->MoveView(m_player.GetPhysicsComponent()->GetPosition());

	m_key.Update(deltaTime.asSeconds());

	if (m_generateNewLevel) {
		m_generateNewLevel = false;
		sf::Vector2f PlayerPos = m_level.GenerateLevel(m_world);
		m_player.GetPhysicsComponent()->SetPosition({ PlayerPos.x, PlayerPos.y });
		m_key.GetSpriteComponent()->GetSprite()->setColor(sf::Color::White);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U)) m_level.UnlockDoor();
}

void Game::Render() {
	m_window->BeginDraw();

	m_window->Draw(m_level);

	m_window->Draw(m_player);
	m_window->Draw(m_key);
	if (m_window->IsDebug()) m_world.DrawDebugData();

	m_window->EndDraw();
}