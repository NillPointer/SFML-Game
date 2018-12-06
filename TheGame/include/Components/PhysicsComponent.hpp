#ifndef PhysicsComponent_hpp
#define PhysicsComponent_hpp

#include "GameObject.hpp"
#include "Util.hpp"

class GameObject;

class PhysicsComponent {
public:
	PhysicsComponent(GameObject& obj, b2World& world);
	virtual ~PhysicsComponent() {};

	void Update(GameObject& obj, float timeDelta);
	void SetVelocity(sf::Vector2f velocity);
	void ResetPosition(sf::Vector2f position);
	sf::Vector2f GetVelocity() const;

private:
	sf::Vector2f m_velocity;

	b2Body* m_body;
	b2World* m_world;
};

#endif // !PhysicsComponent_hpp
