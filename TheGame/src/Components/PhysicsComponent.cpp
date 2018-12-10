#include "Components/PhysicsComponent.hpp"

PhysicsComponent::PhysicsComponent(GameObject& obj, b2Body* body) :
	Component(obj),
	m_body(body)
{}

void PhysicsComponent::Update(float timeDelta) {
	m_body->SetActive(IsActive());
	if (!IsActive()) return;
	m_body->SetLinearVelocity({ m_velocity.x * timeDelta, m_velocity.y * timeDelta });
	m_position = { m_body->GetPosition().x * PIXEL_PER_METER , m_body->GetPosition().y * PIXEL_PER_METER };
}

void PhysicsComponent::SetVelocity(sf::Vector2f velocity) {
	m_velocity = velocity;
}

sf::Vector2f PhysicsComponent::GetVelocity() const {
	return m_velocity;
}

void PhysicsComponent::SetPosition(sf::Vector2f position) {
	m_position = position;
	m_body->SetTransform({ position.x / PIXEL_PER_METER, position.y / PIXEL_PER_METER }, m_body->GetAngle());
}

sf::Vector2f PhysicsComponent::GetPosition() const {
	return m_position;
}