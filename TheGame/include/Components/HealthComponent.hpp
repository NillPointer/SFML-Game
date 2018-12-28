#ifndef HealthComponent_hpp
#define HealthComponent_hpp

#include "GameObject.hpp"
#include "Components/Component.hpp"

class Component;

class HealthComponent: public Component {
public:
	HealthComponent(GameObject& obj, int health = 100);
	~HealthComponent() {};

	void Update(float timeDelta);
	void SetHealth(int health);
	int GetHealth() const;
	void Damage(int damage);
	void ResetHealth();
	bool IsDead();

protected:
	int m_health;
	int m_maxHealth;
};

#endif // !HealthComponent_hpp
