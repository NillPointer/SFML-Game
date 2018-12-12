#include "Commands/Command.hpp"

void Command::Walk(GameObject& obj, sf::Vector2f newVelocity) {
	if (obj.GetPhysicsComponent() == nullptr) return;
	obj.GetPhysicsComponent()->SetVelocity(newVelocity);
}