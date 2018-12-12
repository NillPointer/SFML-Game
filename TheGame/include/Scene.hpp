#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Audio.hpp>
#include "Util.hpp"
#include "Window.hpp"

class Scene {
public:
	Scene(std::shared_ptr<Window> windowptr) : m_window(windowptr), m_changeScene(false), m_isDone(false) {}
	virtual ~Scene() {}
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void RestartClock() = 0;

	sf::Music& GetBackgroundMusic() { return m_backgroundMusic; }
	void StopBackgroundMusic() { m_backgroundMusic.stop(); }
	void PlayBackgroundMusic() { m_backgroundMusic.play(); }

	bool IsChangeScene() { return m_changeScene; }
	void SetChangeScene(bool change) { m_changeScene = change; }

	bool IsDone() { return m_isDone || m_window->IsDone(); }
	void Exit() { m_isDone = true; }

protected:
	std::shared_ptr<Window> m_window;

private:
	sf::Music m_backgroundMusic;
	bool m_changeScene;
	bool m_isDone;
};

#endif // !SCENE_HPP
