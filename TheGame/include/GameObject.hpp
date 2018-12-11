#ifndef GameObject_hpp
#define GameObject_hpp

#include <memory>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Util.hpp"

#include "Components/SpriteComponent.hpp"
#include "Components/AnimatorComponent.hpp"
#include "Components/InuptComponent.hpp"
#include "Components/PhysicsComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "Components/SoundComponent.hpp"

class InputComponent;
class SpriteComponent;
class AnimatorComponent;
class PhysicsComponent;
class HealthComponent;
class SoundComponent;

class GameObject {

public:
	GameObject(): m_name(GAMEOBJECT) {}
	virtual ~GameObject() {}

	void Activate();
	void Deactivate();

	void SetName(std::string name) { m_name = name; }
	std::string GetName() { return m_name; }

	void SetInputComponent(std::shared_ptr<InputComponent> input) { m_input = input; }
	void SetPhysicsComponent(std::shared_ptr<PhysicsComponent> physics) { m_physics = physics; }
	void SetSpriteComponent(std::shared_ptr<SpriteComponent> sprite) { m_sprite = sprite; }
	void SetAnimatorComponent(std::shared_ptr<AnimatorComponent> animator) { m_animator = animator; }
	void SetHealthComponent(std::shared_ptr<HealthComponent> health) { m_health = health; }
	void SetSoundComponent(std::shared_ptr<SoundComponent> sound) { m_sound = sound; }

	std::shared_ptr<InputComponent> GetInputComponent() { return m_input; }
	std::shared_ptr<PhysicsComponent> GetPhysicsComponent() { return m_physics; }
	std::shared_ptr<SpriteComponent> GetSpriteComponent() { return m_sprite; }
	std::shared_ptr<AnimatorComponent> GetAnimatorComponent() { return m_animator; }
	std::shared_ptr<HealthComponent> GetHealthComponent() { return m_health; }
	std::shared_ptr<SoundComponent> GetSoundComponent() { return m_sound; }
private:

	std::shared_ptr<InputComponent> m_input;
	std::shared_ptr<PhysicsComponent> m_physics;
	std::shared_ptr<AnimatorComponent> m_animator;
	std::shared_ptr<SpriteComponent> m_sprite;
	std::shared_ptr<HealthComponent> m_health;
	std::shared_ptr<SoundComponent> m_sound;

	std::string m_name;
};

#endif

