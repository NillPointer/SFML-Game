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
#include "Components/AIComponent.hpp"
#include "Components/NetworkComponent.hpp"
#include "Components/PhysicsComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "Components/SoundComponent.hpp"
#include "Components/AttackComponent.hpp"
#include "Components/InfluenceComponent.hpp"

class InputComponent;
class AIComponent;
class NetworkComponent;
class SpriteComponent;
class AnimatorComponent;
class PhysicsComponent;
class HealthComponent;
class SoundComponent;
class AttackComponent;
class InfluenceComponent;

class GameObject {

public:
	GameObject(): m_name(GAMEOBJECT) {}
	virtual ~GameObject() {}

	void Activate();
	void Deactivate();

	void SetName(char* name) { m_name = name; }
	std::string GetName() { return m_name; }

	void SetInputComponent(std::shared_ptr<InputComponent> input) { m_input = input; }
	void SetAIComponent(std::shared_ptr<AIComponent> ai) { m_ai = ai; }
	void SetNetworkComponent(std::shared_ptr<NetworkComponent> network) { m_network = network; }
	void SetPhysicsComponent(std::shared_ptr<PhysicsComponent> physics) { m_physics = physics; }
	void SetSpriteComponent(std::shared_ptr<SpriteComponent> sprite) { m_sprite = sprite; }
	void SetAnimatorComponent(std::shared_ptr<AnimatorComponent> animator) { m_animator = animator; }
	void SetHealthComponent(std::shared_ptr<HealthComponent> health) { m_health = health; }
	void SetSoundComponent(std::shared_ptr<SoundComponent> sound) { m_sound = sound; }
	void SetAttackComponent(std::shared_ptr<AttackComponent> attack) { m_attack = attack; }
	void SetInfluenceComponent(std::shared_ptr<InfluenceComponent> influence) { m_influence = influence; }

	std::shared_ptr<InputComponent> GetInputComponent() { return m_input; }
	std::shared_ptr<AIComponent> GetAIComponent() { return m_ai; }
	std::shared_ptr<NetworkComponent> GetNetworkComponent() { return m_network; }
	std::shared_ptr<PhysicsComponent> GetPhysicsComponent() { return m_physics; }
	std::shared_ptr<SpriteComponent> GetSpriteComponent() { return m_sprite; }
	std::shared_ptr<AnimatorComponent> GetAnimatorComponent() { return m_animator; }
	std::shared_ptr<HealthComponent> GetHealthComponent() { return m_health; }
	std::shared_ptr<SoundComponent> GetSoundComponent() { return m_sound; }
	std::shared_ptr<AttackComponent> GetAttackComponent() { return m_attack; }
	std::shared_ptr<InfluenceComponent> GetInfluenceComponent() { return m_influence; }
private:

	std::shared_ptr<InputComponent> m_input;
	std::shared_ptr<AIComponent> m_ai;
	std::shared_ptr<NetworkComponent> m_network;
	std::shared_ptr<PhysicsComponent> m_physics;
	std::shared_ptr<AnimatorComponent> m_animator;
	std::shared_ptr<SpriteComponent> m_sprite;
	std::shared_ptr<HealthComponent> m_health;
	std::shared_ptr<SoundComponent> m_sound;
	std::shared_ptr<AttackComponent> m_attack;
	std::shared_ptr<InfluenceComponent> m_influence;

	char* m_name;
};

#endif

