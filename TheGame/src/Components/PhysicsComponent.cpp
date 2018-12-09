#include "Components/PhysicsComponent.hpp"

PhysicsComponent::PhysicsComponent(GameObject& obj, b2World& world, b2Body* body) :
	Component(obj),
	m_world(&world),
	m_body(body)
{}

void PhysicsComponent::Update(float timeDelta) {
	m_body->SetLinearVelocity({ m_velocity.x * timeDelta, m_velocity.y * timeDelta });
	m_position = { m_body->GetPosition().x * PIXEL_PER_METER , m_body->GetPosition().y * PIXEL_PER_METER };
	m_world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
}

void PhysicsComponent::SetVelocity(sf::Vector2f velocity) {
	m_velocity = velocity;
	m_body->SetLinearVelocity({ velocity.x, velocity.y });
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