#ifndef WALKRIGHTCOMMAND_HPP
#define WALKRIGHTCOMMAND_HPP

#include "Commands/Command.hpp"

class GameObject;

class WalkRightCommand : public Command {
public:
	void Execute(GameObject& obj);
};

#endif // !WALKRIGHTCOMMAND_HPP

