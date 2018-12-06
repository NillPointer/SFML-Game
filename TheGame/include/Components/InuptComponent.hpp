#ifndef InputComponent_hpp
#define InputComponent_hpp

#include <map>

#include "GameObject.hpp"
#include "Components/Command.hpp"

class GameObject;
class Command;

class InputComponent {

public:

	enum class KEY {
		KEY_LEFT,
		KEY_RIGHT,
		KEY_UP,
		KEY_DOWN,
		KEY_ATTACK
	};

	InputComponent();
	~InputComponent() {};

	void BindKey(KEY key, sf::Keyboard::Key keyToBind);
	void Update(GameObject& obj);

protected:
	// Default key bindings
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
