#include "Commands/WalkRightCommand.hpp"

void WalkRightCommand::Execute(GameObject& obj) {
	Command::Walk(obj, { PLAYER_WALK_ACCELERATION, 0 });
	if (obj.GetAnimatorComponent() != nullptr) 
		obj.GetAnimatorComponent()->SetCurrentAnimation(static_cast<int>(ANIMATION_STATE::WALK_RIGHT));
}