#include "Components/InuptComponent.hpp"

InputComponent::InputComponent() {
	// Default key binding
	BindKey(KEY::KEY_LEFT, sf::Keyboard::A);
	BindKey(KEY::KEY_RIGHT, sf::Keyboard::D);
	BindKey(KEY::KEY_UP, sf::Keyboard::W);
	BindKey(KEY::KEY_DOWN, sf::Keyboard::S);
	BindKey(KEY::KEY_ATTACK, sf::Keyboard::Space);

	m_keyLeftCommand = std::make_shared<WalkLeftCommand>();
	m_keyRightCommand = std::make_shared<WalkRightCommand>();
	m_keyUpCommand = std::make_shared<WalkUpCommand>();
	m_keyDownCommand = std::make_shared<WalkDownCommand>();
	m_keyAttackCommand = std::make_shared<AttackCommand>();
}

void InputComponent::BindKey(InputComponent::KEY key, sf::Keyboard::Key keyToBind) {
	m_keyMappings[key] = keyToBind;
}

void InputComponent::Update(GameObject& obj) {
	try {
		if (sf::Keyboard::isKeyPressed(m_keyMappings[KEY::KEY_LEFT])) m_keyLeftCommand->Execute(obj);
		else if (sf::Keyboard::isKeyPressed(m_keyMappings[KEY::KEY_RIGHT])) m_keyRightCommand->Execute(obj);
		else if (sf::Keyboard::isKeyPressed(m_keyMappings[KEY::KEY_UP])) m_keyUpCommand->Execute(obj);
		else if (sf::Keyboard::isKeyPressed(m_keyMappings[KEY::KEY_DOWN])) m_keyDownCommand->Execute(obj);
		else if (sf::Keyboard::isKeyPressed(m_keyMappings[KEY::KEY_ATTACK])) m_keyAttackCommand->Execute(obj);
	} catch (const std::exception& e) {
		std::cout << "Key Pressed but not bound" << std::endl;
	}
}