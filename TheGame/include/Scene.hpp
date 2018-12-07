#ifndef SCENE_HPP
#define SCENE_HPP

#include "Util.hpp"
#include "Window.hpp"

class Scene {
public:
	Scene(std::shared_ptr<Window> windowptr) : m_window(windowptr) {}
	virtual ~Scene() {}
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void RestartClock() = 0;

protected:
	std::shared_ptr<Window> m_window;
};

#endif // !SCENE_HPP
