#ifndef PhysicsComponent_hpp
#define PhysicsComponent_hpp

#include <functional>
#include "GameObject.hpp"
#include "Util.hpp"

class GameObject;

class PhysicsComponent: public b2ContactListener {
public:
	PhysicsComponent(GameObject& obj, b2World& world);
	virtual ~PhysicsComponent() {};

	void Update(GameObject& obj, float timeDelta);
	void SetVelocity(sf::Vector2f velocity);
	void SetCollisionCallback(char* collisionWith, std::function<void()> callback);
	void ResetPosition(sf::Vector2f position);
	sf::Vector2f GetVelocity() const;

private:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

	sf::Vector2f m_velocity;

	b2Body* m_body;
	b2World* m_world;

	std::map<char*, std::function<void()>> m_collisionCallbacks;
};

#endif // !PhysicsComponent_hpp
