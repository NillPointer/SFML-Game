#include "Components/PhysicsComponent.hpp"

PhysicsComponent::PhysicsComponent(GameObject& obj, b2World& world) {
	m_world = &world;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(obj.GetPosition().x, obj.GetPosition().y);
	m_body = world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1, 1);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	m_body->CreateFixture(&fixtureDef);
}

void PhysicsComponent::Update(GameObject& obj, float timeDelta){
	//obj.SetPosition(obj.GetPosition() + (m_velocity * timeDelta));
	m_world->Step(timeDelta, 6, 2);
	obj.SetPosition({ m_body->GetPosition().x, m_body->GetPosition().y });
}

void PhysicsComponent::SetVelocity(sf::Vector2f velocity) {
	m_velocity = velocity;
}

sf::Vector2f PhysicsComponent::GetVelocity() const {
	return m_velocity;
}