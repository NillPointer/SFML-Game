#include "Components/PhysicsComponent.hpp"

PhysicsComponent::PhysicsComponent(GameObject& obj, b2World& world) {
	m_world = &world;
	auto posX = obj.GetPosition().x;
	auto posY = obj.GetPosition().y;
	m_body = CreatePhysicsBody(world, { posX, posY }, { 0.45f, 0.45f }, b2_dynamicBody, {0.1f, 0.0f});
	m_world->SetContactListener(this);
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

void PhysicsComponent::BeginContact(b2Contact* contact) {
	//std::cout << "Contact Began" << std::endl;
	auto body = contact->GetFixtureB()->GetBody();
	if (body->GetUserData() != nullptr) {
		char *t = *((char **)contact->GetFixtureB()->GetBody()->GetUserData());
		std::cout << t << std::endl;
	}
}

void PhysicsComponent::EndContact(b2Contact* contact) {
	//std::cout << "Contact Ended" << std::endl;
}

void PhysicsComponent::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
	//std::cout << "Pre Solved" << std::endl;
}

void PhysicsComponent::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
	//std::cout << "Post Solved" << std::endl;
}