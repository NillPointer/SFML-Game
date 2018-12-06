#include "Components/PhysicsComponent.hpp"

PhysicsComponent::PhysicsComponent(GameObject& obj, b2World& world) {
	m_world = &world;
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(obj.GetPosition().x / PIXEL_PER_METER, obj.GetPosition().y / PIXEL_PER_METER);
	m_body = world.CreateBody(&bodyDef);
	
	b2PolygonShape shape;
	b2FixtureDef fixture;
	shape.SetAsBox(0.5f, 0.5f);
	fixture.shape = &shape;
	m_body->CreateFixture(&fixture);
}

void PhysicsComponent::Update(GameObject& obj, float timeDelta) {
	m_body->SetLinearVelocity({ m_velocity.x * timeDelta, m_velocity.y * timeDelta });
	obj.SetPosition({ m_body->GetPosition().x * PIXEL_PER_METER , m_body->GetPosition().y * PIXEL_PER_METER });
	m_world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
}

void PhysicsComponent::SetVelocity(sf::Vector2f velocity) {
	m_velocity = velocity;
	m_body->SetLinearVelocity({ velocity.x, velocity.y });
}

sf::Vector2f PhysicsComponent::GetVelocity() const {
	return m_velocity;
}

void PhysicsComponent::ResetPosition(sf::Vector2f position) {
	m_body->SetTransform({ position.x/ PIXEL_PER_METER, position.y/PIXEL_PER_METER }, m_body->GetAngle());
}