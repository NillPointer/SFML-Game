#include "Components/Command.hpp"

void Command::Walk(GameObject& obj, sf::Vector2f newVelocity) {
	if (obj.GetPhysicsComponent() != nullptr) obj.GetPhysicsComponent()->SetVelocity(newVelocity);
}

void WalkLeftCommand::Execute(GameObject& obj) {
	Command::Walk(obj, { -WALK_ACCELERATION, 0 });
	if (obj.GetGraphicsComponent() != nullptr) obj.GetGraphicsComponent()->SetAnimationState(ANIMATION_STATE::WALK_LEFT);
}

void WalkRightCommand::Execute(GameObject& obj) {
	Command::Walk(obj, { WALK_ACCELERATION, 0 });
	if (obj.GetGraphicsComponent() != nullptr) obj.GetGraphicsComponent()->SetAnimationState(ANIMATION_STATE::WALK_RIGHT);
}

void WalkUpCommand::Execute(GameObject& obj) {
	Command::Walk(obj, { 0, -WALK_ACCELERATION });
	if (obj.GetGraphicsComponent() != nullptr) obj.GetGraphicsComponent()->SetAnimationState(ANIMATION_STATE::WALK_UP);
}

void WalkDownCommand::Execute(GameObject& obj) {
	Command::Walk(obj, { 0, WALK_ACCELERATION });
	if (obj.GetGraphicsComponent() != nullptr) obj.GetGraphicsComponent()->SetAnimationState(ANIMATION_STATE::WALK_DOWN);
}