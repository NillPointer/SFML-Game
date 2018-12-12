#include "Commands/DoNothingCommand.hpp"

void DoNothingCommand::Execute(GameObject& obj) {
	Command::Walk(obj, { 0, 0 });
}