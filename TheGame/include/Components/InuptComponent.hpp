#ifndef InputComponent_hpp
#define InputComponent_hpp

#include <map>

#include "Enums.hpp"
#include "GameObject.hpp"
#include "Components/Command.hpp"
#include "Component.hpp"

class GameObject;
class Command;

class InputComponent: public Component {

public:
	InputComponent(GameObject& obj);
	~InputComponent() {};

	void BindKey(KEY key, sf::Keyboard::Key keyToBind);
	void Update(float timeDelta);

protected:
	// Key bindings map
	std::map<KEY, sf::Keyboard::Key> m_keyMappings;

	std::shared_ptr<Command> m_keyLeftCommand;
	std::shared_ptr<Command> m_keyRightCommand;
	std::shared_ptr<Command> m_keyUpCommand;
	std::shared_ptr<Command> m_keyDownCommand;
	std::shared_ptr<Command> m_keyAttackCommand;

private:
	static const int WALK_ACCELERATION = 1;
};

#endif
