#ifndef PHYSICSCOLLISIONLISTENER_HPP
#define PHYSICSCOLLISIONLISTENER_HPP

#include <functional>
#include <map>
#include "Box2D/Box2D.h"
#include "GameObject.hpp"

class PhysicsCollisionListener: public b2ContactListener {
public:
	void SetCollisionCallback(uint16 collisionMask, std::function<void(GameObject* ptrA, GameObject* ptrB)> callback);

private:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

	std::map<uint16, std::function<void(GameObject* ptrA, GameObject* ptrB)>> m_collisionCallbacks;
};

#endif // !PHYSICSCOLLISIONLISTENER_HPP

