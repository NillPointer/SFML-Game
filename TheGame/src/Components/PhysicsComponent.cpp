#include "Components/PhysicsComponent.hpp"

void PhysicsComponent::Update(GameObject& obj, float timeDelta){
	obj.SetPosition(obj.GetPosition() + (m_velocity * timeDelta));
}

void PhysicsComponent::SetVelocity(sf::Vector2f velocity) {
	m_velocity = velocity;
}

sf::Vector2f PhysicsComponent::GetVelocity() const {
	return m_velocity;
}