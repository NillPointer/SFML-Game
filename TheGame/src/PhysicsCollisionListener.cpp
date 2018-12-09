#include "PhysicsCollisionListener.hpp"
#include <iostream>

void PhysicsCollisionListener::SetCollisionCallback(uint16 collisionMask, std::function<void()> callback) {
	m_collisionCallbacks[collisionMask] = callback;
}

void PhysicsCollisionListener::BeginContact(b2Contact* contact) {
	auto filterA = contact->GetFixtureA()->GetFilterData();
	auto filterB = contact->GetFixtureB()->GetFilterData();

	uint16 collision = filterA.categoryBits | filterB.categoryBits;

	if (m_collisionCallbacks.find(collision) != m_collisionCallbacks.end()) m_collisionCallbacks[collision]();
}

void PhysicsCollisionListener::EndContact(b2Contact* contact) {
}

void PhysicsCollisionListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
}

void PhysicsCollisionListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
}