#ifndef GameObject_hpp
#define GameObject_hpp

#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Components/GraphicsComponent.hpp"
#include "Components/InuptComponent.hpp"
#include "Components/PhysicsComponent.hpp"

class InputComponent;
class GraphicsComponent;
class PhysicsComponent;

class GameObject: public sf::Drawable {

public:
	GameObject();
	virtual ~GameObject() {};

	virtual void Update(float timeDelta);
	
	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition() const { return m_position; }
	
	void SetInfluence(float influence) { m_influenceValue = influence; }
	float GetInfluence() const { return m_influenceValue; }

	void SetInputComponent(std::shared_ptr<InputComponent> input) { m_input = input; }
	void SetPhysicsComponent(std::shared_ptr<PhysicsComponent> physics) { m_physics = physics; }
	void SetGraphicsComponent(std::shared_ptr<GraphicsComponent> graphics) { m_graphics = graphics; }

	std::shared_ptr<InputComponent> GetInputComponent() { return m_input; }
	std::shared_ptr<PhysicsComponent> GetPhysicsComponent() { return m_physics; }
	std::shared_ptr<GraphicsComponent> GetGraphicsComponent() { return m_graphics; }

protected:
	sf::Vector2f m_position;
	float m_influenceValue;

	std::shared_ptr<InputComponent> m_input;
	std::shared_ptr<PhysicsComponent> m_physics;
	std::shared_ptr<GraphicsComponent> m_graphics;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif

