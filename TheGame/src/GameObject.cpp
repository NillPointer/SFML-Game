#include "GameObject.hpp"

void GameObject::Activate() {
	if (m_input != nullptr) m_input->SetActive(true);
	if (m_physics != nullptr) m_physics->SetActive(true);
	if (m_animator != nullptr) m_animator->SetActive(true);
	if (m_sprite != nullptr) m_sprite->SetActive(true);
	if (m_health != nullptr) m_health->SetActive(true);
	if (m_sound != nullptr) m_sound->SetActive(true);
	if (m_ai != nullptr) m_ai->SetActive(true);
	if (m_attack != nullptr) m_attack->SetActive(true);
	if (m_network != nullptr) m_network->SetActive(true);
}

void GameObject::Deactivate() {
	if (m_input != nullptr) m_input->SetActive(false);
	if (m_physics != nullptr) m_physics->SetActive(false);
	if (m_animator != nullptr) m_animator->SetActive(false);
	if (m_sprite != nullptr) m_sprite->SetActive(false);
	if (m_sound != nullptr) m_sound->SetActive(true);
	if (m_health != nullptr) m_health->SetActive(false);
	if (m_ai != nullptr) m_ai->SetActive(true);
	if (m_attack != nullptr) m_attack->SetActive(true);
	if (m_network != nullptr) m_network->SetActive(true);
}