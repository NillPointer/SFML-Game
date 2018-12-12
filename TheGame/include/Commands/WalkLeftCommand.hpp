#ifndef WALKLEFTCOMMAND_HPP
#define WALKLEFTCOMMAND_HPP

#include "Commands/Command.hpp"

class GameObject;

class WalkLeftCommand : public Command {
public:
	void Execute(GameObject& obj);
};

#endif // !WALKLEFTCOMMAND_HPP
