#ifndef HealthComponent_hpp
#define HealthComponent_hpp

class HealthComponent {
public:
	HealthComponent() {};
	HealthComponent(int health) : m_health(health) {};
	~HealthComponent() {};

	void SetHealth(int health) { m_health = health;  }
	int GetHealth() const { return m_health; }
	void Damage(int damage) { m_health -= damage; }
	bool IsDead() { return m_health > 0; }

protected:
	int m_health;
	int m_maxHealth;
};

#endif // !HealthComponent_hpp
