#include "Window.hpp"

Window::Window() { Setup(); }
Window::~Window() { Destroy(); }

void Window::Setup() {
	m_windowTitle = WINDOW_TITLE;
	m_windowSize = { WINDOW_WIDTH, WINDOW_HEIGHT };
	m_isFullscreen = false;
	m_isDone = false;
	Create();
}

void Window::Create() {
	auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, style);
}

void Window::Destroy() {
	m_window.close();
}

void Window::BeginDraw() { m_window.clear(sf::Color::Black); }
void Window::Draw(sf::Drawable &drawable) { m_window.draw(drawable); }
void Window::EndDraw() { m_window.display(); }

bool Window::IsDone() { return m_isDone; }
bool Window::IsFullscreen() { return m_isFullscreen; }
bool Window::IsDebug() { return m_isDebug; }

sf::RenderWindow* Window::GetRenderWindow() { return &m_window; }
sf::Vector2u Window::GetWindowSize() { return m_windowSize; }

void Window::ToggleFullscreen() {
	m_isFullscreen = !m_isFullscreen;
	m_window.close();
	Create();
}

void Window::Update() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) { m_isDone = true; }
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) { m_isDone = true; }
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) { ToggleFullscreen(); }
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) { m_isDebug = !m_isDebug; }
	}
}