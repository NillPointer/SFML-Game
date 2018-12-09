#ifndef HealthComponent_hpp
#define HealthComponent_hpp

#include "GameObject.hpp"
#include "Components/Component.hpp"

class Component;

class HealthComponent: public Component {
public:
	HealthComponent(GameObject& obj): Component(obj) {}
	HealthComponent(GameObject& obj, int health) : Component(obj), m_health(health) {}
	~HealthComponent() {};

	void Update(float timeDelta) {}
	void SetHealth(int health) { m_health = health;  }
	int GetHealth() const { return m_health; }
	void Damage(int damage) { m_health -= damage; }
	bool IsDead() { return m_health > 0; }

protected:
	int m_health;
	int m_maxHealth;
};

#endif // !HealthComponent_hpp
