#include "Game.hpp"

Game::Game(): m_world(b2Vec2(0,10)), m_player(m_world) {
	m_clock.restart();
	m_previousTime = m_clock.getElapsedTime();
	srand(time(nullptr));

	m_font.loadFromFile("resource/fonts/ADDSBP__.TTF");
	m_level = Level(*m_window.GetRenderWindow());
	m_level.LoadLevelFromFile("resource/data/level_data.txt");

	m_player.SetPosition({ m_window.GetWindowSize().x / 2.f, m_window.GetWindowSize().y / 2.f });

	m_window.GetRenderWindow()->setFramerateLimit(FPS);
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
	m_window.Update();
	sf::Time deltaTime = m_clock.getElapsedTime() - GetElapsed();

	m_player.Update(deltaTime.asSeconds());

	m_window.MoveView(m_player.GetPosition());
}

void Game::Render() {
	m_window.BeginDraw();

	m_window.Draw(m_level);

	m_window.Draw(m_player);

	m_window.EndDraw();
}