#include "Game.hpp"

Game::Game(std::shared_ptr<Window> windowprt):
	Scene(windowprt), m_world(b2Vec2(0,0)),
	m_player(m_world),
	m_debugDraw(*m_window->GetRenderWindow())
{
	m_clock.restart();
	m_previousTime = m_clock.getElapsedTime();
	srand(time(nullptr));

	m_world.SetDebugDraw(&m_debugDraw);
	m_debugDraw.SetFlags(b2Draw::e_shapeBit);

	m_font.loadFromFile("resource/fonts/ADDSBP__.TTF");
	m_level = Level(*m_window->GetRenderWindow());
	sf::Vector2f PlayerPos = m_level.GenerateLevel(m_world);

	m_player.SetPosition({ PlayerPos.x, PlayerPos.y });
	m_window->GetRenderWindow()->setFramerateLimit(FPS);
}

Game::~Game() {}

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

	m_window->MoveView(m_player.GetPosition());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		sf::Vector2f PlayerPos = m_level.GenerateLevel(m_world);
		m_player.SetPosition({ PlayerPos.x, PlayerPos.y });
	}
}

void Game::Render() {
	m_window->BeginDraw();

	m_window->Draw(m_level);

	m_window->Draw(m_player);

	m_world.DrawDebugData();

	m_window->EndDraw();
}