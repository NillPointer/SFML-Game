#ifndef PLAYER_HPP

#include "GameObject.hpp"
#include "Components/HealthComponent.hpp"

class Player : public GameObject {
public:
	Player(b2World& world);
	void Update(float timeDelta);
	void SetHealth(int healthValue);
	PLAYER_CLASS GetClass() const;

private:
	std::shared_ptr<HealthComponent> m_health;
	PLAYER_CLASS m_class;

};

#endif // !PLAYER_HPP

