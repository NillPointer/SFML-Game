#include "Components/PhysicsComponent.hpp"

PhysicsComponent::PhysicsComponent(GameObject& obj, b2World& world): Component(obj) {
	m_world = &world;
	m_body = CreatePhysicsBody(world, { 0, 0 }, { 0.45f, 0.45f }, b2_dynamicBody);
	m_world->SetContactListener(this);
}

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

void PhysicsComponent::SetCollisionCallback(char* collisionWith, std::function<void()> callback) {
	m_collisionCallbacks[collisionWith] = callback;
}

void PhysicsComponent::BeginContact(b2Contact* contact) {
//	std::cout << "Contact Began" << std::endl;
	auto body = contact->GetFixtureB()->GetBody();
	if (body->GetUserData() != nullptr) {
		char* collidedWith = *((char **)contact->GetFixtureB()->GetBody()->GetUserData());
		if (collidedWith != nullptr && m_collisionCallbacks.find(collidedWith) != m_collisionCallbacks.end()) {
			m_collisionCallbacks[collidedWith]();
		}
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