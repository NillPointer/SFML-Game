#include "Components/Command.hpp"

void Command::Walk(GameObject& obj, sf::Vector2f newVelocity) {
	if (obj.GetPhysicsComponent() != nullptr) obj.GetPhysicsComponent()->SetVelocity(newVelocity);
}

void WalkLeftCommand::Execute(GameObject& obj) {
	Command::Walk(obj, { -PLAYER_WALK_ACCELERATION, 0 });
	if (obj.GetAnimatorComponent() != nullptr) obj.GetAnimatorComponent()->SetCurrentAnimation(static_cast<int>(ANIMATION_STATE::WALK_LEFT));
}

void WalkRightCommand::Execute(GameObject& obj) {
	Command::Walk(obj, { PLAYER_WALK_ACCELERATION, 0 });
	if (obj.GetAnimatorComponent() != nullptr) obj.GetAnimatorComponent()->SetCurrentAnimation(static_cast<int>(ANIMATION_STATE::WALK_RIGHT));
}

void WalkUpCommand::Execute(GameObject& obj) {
	Command::Walk(obj, { 0, -PLAYER_WALK_ACCELERATION });
	if (obj.GetAnimatorComponent() != nullptr) obj.GetAnimatorComponent()->SetCurrentAnimation(static_cast<int>(ANIMATION_STATE::WALK_UP));
}

void WalkDownCommand::Execute(GameObject& obj) {
	Command::Walk(obj, { 0, PLAYER_WALK_ACCELERATION });
	if (obj.GetAnimatorComponent() != nullptr) obj.GetAnimatorComponent()->SetCurrentAnimation(static_cast<int>(ANIMATION_STATE::WALK_DOWN));
}

void DoNothingCommand::Execute(GameObject& obj) {
	Command::Walk(obj, { 0, 0 });
}