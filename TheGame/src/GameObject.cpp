#include "GameObject.hpp"

GameObject::GameObject() {}

void GameObject::Update(float timeDelta) {
	if (m_input != nullptr) m_input->Update(timeDelta);
	if (m_physics != nullptr) m_physics->Update(timeDelta);
	//if (m_graphics != nullptr) m_graphics->Update(timeDelta);
	if (m_physics != nullptr) m_physics->SetVelocity({ 0,0 });
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	//if (m_graphics != nullptr) m_graphics->Draw(target);
}