#ifndef PhysicsComponent_hpp
#define PhysicsComponent_hpp

#include "GameObject.hpp"
#include "Components/Component.hpp"
#include "Util.hpp"

class Component;

class PhysicsComponent: public Component {
public:
	PhysicsComponent(GameObject& obj, b2Body* body);
	virtual ~PhysicsComponent() {};

	void Update(float timeDelta);

	void SetVelocity(sf::Vector2f velocity);
	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetVelocity() const;
	sf::Vector2f GetPosition() const;

private:
	b2Body* m_body;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
};

#endif // !PhysicsComponent_hpp
