#include "PhysicsCollisionListener.hpp"
#include <iostream>
#include "Util.hpp"
#include "GameObject.hpp"

void PhysicsCollisionListener::SetCollisionCallback(uint16 collisionMask, std::function<void(GameObject* ptrA, GameObject* ptrB)> callback) {
	m_collisionCallbacks[collisionMask] = callback;
}

void PhysicsCollisionListener::BeginContact(b2Contact* contact) {
	auto filterA = contact->GetFixtureA()->GetFilterData();
	auto filterB = contact->GetFixtureB()->GetFilterData();

	uint16 collision = filterA.categoryBits | filterB.categoryBits;

	if (m_collisionCallbacks.find(collision) != m_collisionCallbacks.end()) {
		GameObject* a = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData();
		GameObject* b = (GameObject*)contact->GetFixtureB()->GetBody()->GetUserData();
		GameObject* playerOrProjectile = nullptr;
		GameObject* other = nullptr;
		if (a != nullptr) playerOrProjectile = (a->GetName() == PLAYER_ENTITY || a->GetName() == PROJECTILE_ENTITY) ? a : b;
		else if (b != nullptr) playerOrProjectile = (b->GetName() == PLAYER_ENTITY || b->GetName() == PROJECTILE_ENTITY) ? b : a;
		other = playerOrProjectile == a ? b : a;
		m_collisionCallbacks[collision](playerOrProjectile, other);
	}
}

void PhysicsCollisionListener::EndContact(b2Contact* contact) {
}

void PhysicsCollisionListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
}

void PhysicsCollisionListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
}