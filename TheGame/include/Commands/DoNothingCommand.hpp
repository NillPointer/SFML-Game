#ifndef DONOTHINGCOMMAND_HPP
#define DONOTHINGCOMMAND_HPP

#include "Commands/Command.hpp"

class GameObject;

class DoNothingCommand : public Command {
public:
	void Execute(GameObject& obj);
};

#endif // !DONOTHINGCOMMAND_HPP

