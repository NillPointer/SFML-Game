#include "Commands/AttackCommand.hpp"

void AttackCommand::Execute(GameObject& obj) {
	if (obj.GetAttackComponent() != nullptr) obj.GetAttackComponent()->Attack();
}