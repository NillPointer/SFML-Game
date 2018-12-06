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

class AttackCommand : public Command {
	void Execute(GameObject& obj) {
		std::cout << "Attack Not Implemented" << std::endl;
	}
};

class WalkLeftCommand : public Command {
public:
	void Execute(GameObject& obj);
};

class WalkRightCommand : public Command {
public:
	void Execute(GameObject& obj);
};

class WalkUpCommand : public Command {
public:
	void Execute(GameObject& obj);
};

class WalkDownCommand : public Command {
public:
	void Execute(GameObject& obj);
};

#endif // !Command_hpp

