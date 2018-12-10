#include "PhysicsCollisionListener.hpp"
#include <iostream>
#include "Util.hpp"

void PhysicsCollisionListener::SetCollisionCallback(uint16 collisionMask, std::function<void(void* ptr)> callback) {
	m_collisionCallbacks[collisionMask] = callback;
}

void PhysicsCollisionListener::BeginContact(b2Contact* contact) {
	auto filterA = contact->GetFixtureA()->GetFilterData();
	auto filterB = contact->GetFixtureB()->GetFilterData();

	uint16 collision = filterA.categoryBits | filterB.categoryBits;

	if (m_collisionCallbacks.find(collision) != m_collisionCallbacks.end()) {
		void* notPlayer = filterA.categoryBits != PLAYER ?
			contact->GetFixtureA()->GetBody()->GetUserData() : contact->GetFixtureB()->GetBody()->GetUserData();
		m_collisionCallbacks[collision](notPlayer);
	}
}

void PhysicsCollisionListener::EndContact(b2Contact* contact) {
}

void PhysicsCollisionListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
}

void PhysicsCollisionListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
}