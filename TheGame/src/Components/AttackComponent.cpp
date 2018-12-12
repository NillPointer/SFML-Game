#include "Components/AttackComponent.hpp"
#include "Util.hpp"
#include "AssetManager.hpp"

AttackComponent::AttackComponent(GameObject & obj, b2World& world, PhysicsCollisionListener& listener, int poolSize):
	Component(obj),
	m_world(world),
	m_projectilePool(poolSize),
	m_cooldown(0)
{
	m_collisionWithEnemyCallback = [&](GameObject* a, GameObject* b) { b->Deactivate(); m_collisionWithWallCallback(a, b); };
	m_collisionWithWallCallback = [&](GameObject* a, GameObject* b) { m_toBeDeletedFromPool.push_back(a); };

	listener.SetCollisionCallback(PROJECTILE | ENEMY, m_collisionWithEnemyCallback);
	listener.SetCollisionCallback(PROJECTILE | WALL, m_collisionWithWallCallback);
}

AttackComponent::~AttackComponent() {
	m_projectilePool.delete_all();
}

void AttackComponent::Update(float timeDelta) {
	if (!IsActive()) return;
	m_cooldown += timeDelta;

	m_projectilePool.for_each([timeDelta](GameObject* obj) {
		obj->GetPhysicsComponent()->Update(timeDelta);
		obj->GetSpriteComponent()->Update(timeDelta);
	});
}

void AttackComponent::DestroyProjectiles() {
	if (m_world.IsLocked()) return;
	for (auto projectile : m_toBeDeletedFromPool) {
		auto body = projectile->GetPhysicsComponent()->GetBody();
		for (auto b = 0; b < m_world.GetBodyCount(); b++) if (body == m_world.GetBodyList()+b) m_world.DestroyBody(body);
		//if (body == (b2Body*)0xDDDDDDDD) m_world.DestroyBody(body); //IF ALL ELSE FAILS, USE THIS
		m_projectilePool.delete_object(projectile);
	}
	m_toBeDeletedFromPool.clear();
}

void AttackComponent::Attack() {
	if (m_cooldown < PROJECTILE_COOLDOWN) return;
	m_cooldown = 0.0f;
	if (m_gameObject.GetPhysicsComponent() == nullptr) return;

	GameObject* obj = m_projectilePool.new_object();
	obj->SetName(PROJECTILE_ENTITY);
	b2Body* body = CreateCirclePhysicsBody(m_world, { 0, 0 }, 0.25f, b2_dynamicBody);
	SetPhysicsBodyFilter(body, PROJECTILE);
	body->SetUserData(obj);

	obj->SetSpriteComponent(std::make_shared<SpriteComponent>(*obj));
	obj->SetPhysicsComponent(std::make_shared<PhysicsComponent>(*obj, body));
	obj->GetSpriteComponent()->SetSprite(AssetManager::AddTexture("resource/projectiles/spr_magic_ball.png"));

	auto position = m_gameObject.GetPhysicsComponent()->GetPosition();
	auto direction = m_gameObject.GetPhysicsComponent()->GetFacingDirection();
	obj->GetPhysicsComponent()->SetPosition(position + (direction * PIXEL_PER_METER));
	obj->GetPhysicsComponent()->SetVelocity(direction * PROJECTILE_ACCELERATION);
}

void AttackComponent::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	if (!IsActive()) return;
	m_projectilePool.for_each([&target](GameObject* obj) {
		target.draw(*obj->GetSpriteComponent());
	});
}
