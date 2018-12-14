#ifndef ATTACKCOMPONENT_HPP
#define ATTACKCOMPONENT_HPP

#include <functional>
#include <set>
#include "bitshifter/ObjectPool.hpp"
#include "GameObject.hpp"
#include "Components/Component.hpp"
#include "PhysicsCollisionListener.hpp"

class Component;
class PhysicsCollisionListener;

class AttackComponent : public Component, public sf::Drawable {
public:
	AttackComponent(GameObject& obj, b2World& world, PhysicsCollisionListener& listener, int poolSize = 64);
	~AttackComponent();
	void Update(float timeDelta);

	void Attack();
	void DestroyProjectiles();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::function<void(GameObject*, GameObject*)> m_collisionWithWallCallback;
	std::function<void(GameObject*, GameObject*)> m_collisionWithEnemyCallback;
	std::function<void(GameObject*, GameObject*)> m_collisionWithSelfCallback;

	FixedObjectPool<GameObject> m_projectilePool;
	std::set<GameObject*> m_toBeDeletedFromPool;

	b2World* m_world;

	float m_cooldown;
};

#endif // !ATTACKCOMPONENT_HPP
