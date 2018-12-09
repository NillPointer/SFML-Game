#include "Player.hpp"
#include <iostream>
#include "Util.hpp"
#include "TextureManager.hpp"

Player::Player(b2World& world) {
	m_animator = std::make_shared<AnimatorComponent>(*this);
	m_sprite = std::make_shared<SpriteComponent>(*this);
	m_physics = std::make_shared<PhysicsComponent>(*this, world);
	m_input = std::make_shared<InputComponent>(*this);
	m_health = std::make_shared<HealthComponent>(*this);

	std::string prefix = "resource/players/mage/spr_mage";
	std::string textures[] = {prefix+"_walk_up.png", prefix + "_walk_down.png",prefix + "_walk_right.png",prefix + "_walk_left.png",
							prefix + "_idle_up.png", prefix + "_idle_down.png",prefix + "_idle_right.png",prefix + "_idle_left.png" };
	for (int i = 0; i < static_cast<int>(ANIMATION_STATE::COUNT); ++i) {
		m_animator->AddAnimation(i, TextureManager::AddTexture(textures[i]));
		auto size = m_animator->GetAnimation(i).GetTexture().getSize();
		auto frames = size.x > 33 ? 8 : 1;
		for (int j = 0; j < frames; ++j) m_animator->GetAnimation(i).AddFrame({ ((int)size.x / frames) * j, 0, 33, 33 });
	}
}

// Updates the player object.
void Player::Update(float timeDelta) {
	GameObject::Update(timeDelta);
}

// Returns the player's class.
PLAYER_CLASS Player::GetClass() const {
	return m_class;
}

// Set the player's health.
void Player::SetHealth(int healthValue) {
	if (m_health == nullptr) return;

	m_health->SetHealth(healthValue);
}