#include "Game.hpp"

Game::Game() {
	m_clock.restart();
	m_previousTime = m_clock.getElapsedTime();
	srand(time(nullptr));

	m_window.GetRenderWindow()->setFramerateLimit(60);
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
}

void Game::Render() {
	m_window.BeginDraw();
	m_window.EndDraw();
}