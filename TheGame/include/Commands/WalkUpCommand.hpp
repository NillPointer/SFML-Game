#ifndef WALKUPCOMMAND_HPP
#define WALKUPCOMMAND_HPP

#include "Commands/Command.hpp"

class GameObject;

class WalkUpCommand : public Command {
public:
	void Execute(GameObject& obj);
};

#endif // !WALKUPCOMMAND_HPP

