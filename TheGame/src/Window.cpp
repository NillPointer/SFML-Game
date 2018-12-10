#include "Window.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

Window::Window() { Setup(); }
Window::~Window() { Destroy(); }

void Window::Setup() {
	m_windowTitle = WINDOW_TITLE;
	m_windowSize = { WINDOW_WIDTH, WINDOW_HEIGHT };
	m_isFullscreen = false;
	m_isDone = false;
	m_isDebug = true;
	m_views[static_cast<int>(VIEW::MAIN)] = sf::View({ 0,0 }, { (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT });
	m_views[static_cast<int>(VIEW::UI)] = sf::View({ 0,0 }, { (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT });
	m_views[static_cast<int>(VIEW::DEBUG)] = sf::View({ 0,0 }, { (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT });
	m_views[static_cast<int>(VIEW::DEBUG)].zoom(1.7f);
	m_currentView = VIEW::MAIN;
	Create();
}

void Window::Create() {
	auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, style);
	m_window.setView(m_views[static_cast<int>(VIEW::MAIN)]);
}

void Window::Destroy() {
	m_window.close();
}

void Window::BeginDraw() { m_window.clear(sf::Color::Black); }
void Window::Draw(sf::Drawable &drawable) { m_window.draw(drawable); }
void Window::EndDraw() { m_window.display(); }

void Window::MoveView(sf::Vector2f position) {
	if (m_isDebug) m_currentView = VIEW::DEBUG;
	else m_currentView = VIEW::MAIN;
	m_views[static_cast<int>(m_currentView)].setCenter(position);
	m_window.setView(m_views[static_cast<int>(m_currentView)]);
}

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
		ImGui::SFML::ProcessEvent(event);
		if (event.type == sf::Event::Closed) { m_isDone = true; }
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) { m_isDone = true; }
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) { ToggleFullscreen(); }
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F2) { m_isDebug = !m_isDebug; }
		else if (event.type == sf::Event::Resized) {
			m_views[static_cast<int>(m_currentView)].reset(sf::FloatRect(0.0f, 0.0f, event.size.width, event.size.height));
			m_window.setView(m_views[static_cast<int>(m_currentView)]);
		}
	}
}