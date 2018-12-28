#include "Components/HealthComponent.hpp"

HealthComponent::HealthComponent(GameObject& obj, int health) :
	Component(obj),
	m_health(health),
	m_maxHealth(health) {}

void HealthComponent::Update(float timeDelta) {
	if (!IsActive()) return;

	if (IsDead()) m_gameObject.Deactivate();
}

void HealthComponent::SetHealth(int health) {
	m_health = health;
}

int HealthComponent::GetHealth() const {
	return m_health;
}

void HealthComponent::Damage(int damage) {
	m_health -= damage;
}

bool HealthComponent::IsDead() {
	return m_health <= 0;
}

void HealthComponent::ResetHealth() {
	m_health = m_maxHealth;
}

