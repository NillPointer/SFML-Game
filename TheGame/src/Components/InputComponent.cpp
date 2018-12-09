#include "Components/InuptComponent.hpp"

InputComponent::InputComponent(GameObject& obj): Component(obj) {
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
	m_doNothingCommand = std::make_shared<DoNothingCommand>();
}

void InputComponent::BindKey(KEY key, sf::Keyboard::Key keyToBind) {
	m_keyMappings[key] = keyToBind;
}

void InputComponent::Update(float timeDelta) {
	try {
		if (sf::Keyboard::isKeyPressed(m_keyMappings[KEY::KEY_LEFT])) m_keyLeftCommand->Execute(m_gameObject);
		else if (sf::Keyboard::isKeyPressed(m_keyMappings[KEY::KEY_RIGHT])) m_keyRightCommand->Execute(m_gameObject);
		else if (sf::Keyboard::isKeyPressed(m_keyMappings[KEY::KEY_UP])) m_keyUpCommand->Execute(m_gameObject);
		else if (sf::Keyboard::isKeyPressed(m_keyMappings[KEY::KEY_DOWN])) m_keyDownCommand->Execute(m_gameObject);
		else if (sf::Keyboard::isKeyPressed(m_keyMappings[KEY::KEY_ATTACK])) m_keyAttackCommand->Execute(m_gameObject);
		else m_doNothingCommand->Execute(m_gameObject);
	} catch (const std::exception& e) {
		std::cout << "Key Pressed but not bound" << std::endl;
	}
}