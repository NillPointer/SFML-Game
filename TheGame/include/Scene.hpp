#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Audio.hpp>
#include "Util.hpp"
#include "Window.hpp"

class Scene {
public:
	Scene(std::shared_ptr<Window> windowptr) : m_window(windowptr), m_mode(GAME_MODE::NA), m_changeScene(false), m_isDone(false) {}
	virtual ~Scene() {}
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void RestartClock() = 0;
	virtual void Initialize(bool networking = false, bool host = false,int seed = -1) {}

	sf::Music& GetBackgroundMusic() { return m_backgroundMusic; }
	void StopBackgroundMusic() { m_backgroundMusic.stop(); }
	void PlayBackgroundMusic() { m_backgroundMusic.play(); }

	bool IsChangeScene() { return m_changeScene; }
	GAME_MODE GetSceneData() { return m_mode; }
	void SetChangeScene(bool change) { m_changeScene = change; }

	bool IsDone() { return m_isDone || m_window->IsDone(); }
	void Exit() { m_isDone = true; }

protected:
	std::shared_ptr<Window> m_window;
	GAME_MODE m_mode;

private:
	sf::Music m_backgroundMusic;
	bool m_changeScene;
	bool m_isDone;
};

#endif // !SCENE_HPP
