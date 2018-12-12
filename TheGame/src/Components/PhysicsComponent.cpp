#include "Components/PhysicsComponent.hpp"

PhysicsComponent::PhysicsComponent(GameObject& obj, b2Body* body) :
	Component(obj),
	m_body(body),
	m_facingDirection(0, -1)
{}

void PhysicsComponent::Update(float timeDelta) {
	m_body->SetActive(IsActive());
	if (!IsActive() || m_body == nullptr) return;
	m_body->SetLinearVelocity({ m_velocity.x * timeDelta, m_velocity.y * timeDelta });
	m_position = { m_body->GetPosition().x * PIXEL_PER_METER , m_body->GetPosition().y * PIXEL_PER_METER };
}

void PhysicsComponent::SetVelocity(sf::Vector2f velocity) {
	m_velocity = velocity;
	if (velocity.x != 0 || velocity.y != 0) m_facingDirection = Normalize(m_velocity);
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

sf::Vector2f PhysicsComponent::GetFacingDirection() const {
	return m_facingDirection;
}

b2Body* PhysicsComponent::GetBody() {
	return m_body;
}