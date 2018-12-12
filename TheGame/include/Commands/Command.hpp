#ifndef Command_hpp
#define Command_hpp

#include "GameObject.hpp"
#include "Components/PhysicsComponent.hpp"
#include "Enums.hpp"

class GameObject;

class Command {
public:
	virtual ~Command() {}
	virtual void Execute(GameObject& obj) = 0;

protected:
	void Walk(GameObject& obj, sf::Vector2f newVelocity);
};

#endif // !Command_hpp

