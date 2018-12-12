#ifndef WALKDOWNCOMMAND_HPP
#define WALKDOWNCOMMAND_HPP

#include "Commands/Command.hpp"

class GameObject;

class WalkDownCommand : public Command {
public:
	void Execute(GameObject& obj);
};

#endif // !WALKDOWNCOMMAND_HPP

