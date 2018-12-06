#ifndef PhysicsComponent_hpp
#define PhysicsComponent_hpp

#include "GameObject.hpp"

class GameObject;

class PhysicsComponent {
public:
	PhysicsComponent() {};
	virtual ~PhysicsComponent() {};

	void Update(GameObject& obj, float timeDelta);
	void SetVelocity(sf::Vector2f velocity);
	sf::Vector2f GetVelocity() const;

private:
	sf::Vector2f m_velocity;
};

#endif // !PhysicsComponent_hpp
