#ifndef GameObject_hpp
#define GameObject_hpp

#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Components/SpriteComponent.hpp"
#include "Components/AnimatorComponent.hpp"
#include "Components/InuptComponent.hpp"
#include "Components/PhysicsComponent.hpp"
#include "Components/HealthComponent.hpp"

class InputComponent;
class SpriteComponent;
class AnimatorComponent;
class PhysicsComponent;
class HealthComponent;

class GameObject {

public:
	GameObject() {}
	virtual ~GameObject() {}

	void SetInputComponent(std::shared_ptr<InputComponent> input) { m_input = input; }
	void SetPhysicsComponent(std::shared_ptr<PhysicsComponent> physics) { m_physics = physics; }
	void SetSpriteComponent(std::shared_ptr<SpriteComponent> sprite) { m_sprite = sprite; }
	void SetAnimatorComponent(std::shared_ptr<AnimatorComponent> animator) { m_animator = animator; }
	void SetHealthComponent(std::shared_ptr<HealthComponent> health) { m_health = health; }

	std::shared_ptr<InputComponent> GetInputComponent() { return m_input; }
	std::shared_ptr<PhysicsComponent> GetPhysicsComponent() { return m_physics; }
	std::shared_ptr<SpriteComponent> GetSpriteComponent() { return m_sprite; }
	std::shared_ptr<AnimatorComponent> GetAnimatorComponent() { return m_animator; }
	std::shared_ptr<HealthComponent> GetHealthComponent() { return m_health; }

private:

	std::shared_ptr<InputComponent> m_input;
	std::shared_ptr<PhysicsComponent> m_physics;
	std::shared_ptr<AnimatorComponent> m_animator;
	std::shared_ptr<SpriteComponent> m_sprite;
	std::shared_ptr<HealthComponent> m_health;
};

#endif

