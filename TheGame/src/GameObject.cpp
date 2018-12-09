#include "GameObject.hpp"

GameObject::GameObject() {}

void GameObject::Update(float timeDelta) {
	if (m_input != nullptr) m_input->Update(timeDelta);
	if (m_physics != nullptr) m_physics->Update(timeDelta);
	if (m_animator != nullptr) m_animator->Update(timeDelta);
	if (m_sprite != nullptr) m_sprite->Update(timeDelta);
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	if (m_sprite != nullptr) target.draw(*m_sprite);
}