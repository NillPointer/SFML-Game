#ifndef ATTACKCOMMAND_HPP
#define ATTACKCOMMAND_HPP

#include "Commands/Command.hpp"

class GameObject;

class AttackCommand : public Command {
public:
	void Execute(GameObject& obj);
};

#endif // !ATTACKCOMMAND_HPP

