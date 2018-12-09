#ifndef GameObject_hpp
#define GameObject_hpp

#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Components/GraphicsComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/InuptComponent.hpp"
#include "Components/PhysicsComponent.hpp"

class InputComponent;
class GraphicsComponent;
class SpriteComponent;
class PhysicsComponent;

class GameObject: public sf::Drawable {

public:
	GameObject();
	virtual ~GameObject() {};

	virtual void Update(float timeDelta);

	void SetInputComponent(std::shared_ptr<InputComponent> input) { m_input = input; }
	void SetPhysicsComponent(std::shared_ptr<PhysicsComponent> physics) { m_physics = physics; }
	void SetSpriteComponent(std::shared_ptr<SpriteComponent> sprite) { m_sprite = sprite; }
	//void SetGraphicsComponent(std::shared_ptr<GraphicsComponent> graphics) { m_graphics = graphics; }

	std::shared_ptr<InputComponent> GetInputComponent() { return m_input; }
	std::shared_ptr<PhysicsComponent> GetPhysicsComponent() { return m_physics; }
	std::shared_ptr<SpriteComponent> GetSpriteComponent() { return m_sprite; }
	std::shared_ptr<GraphicsComponent> GetGraphicsComponent() { return nullptr; }

protected:

	std::shared_ptr<InputComponent> m_input;
	std::shared_ptr<PhysicsComponent> m_physics;
	std::shared_ptr<SpriteComponent> m_sprite;
	//std::shared_ptr<GraphicsComponent> m_graphics;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif

