#include "Commands/WalkDownCommand.hpp"

void WalkDownCommand::Execute(GameObject& obj) {
	Command::Walk(obj, { 0, PLAYER_WALK_ACCELERATION });
	if (obj.GetAnimatorComponent() != nullptr) 
		obj.GetAnimatorComponent()->SetCurrentAnimation(static_cast<int>(ANIMATION_STATE::WALK_DOWN));
}