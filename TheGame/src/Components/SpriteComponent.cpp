#include "Components/SpriteComponent.hpp"
#include "TextureManager.hpp"

SpriteComponent::SpriteComponent(GameObject & obj) : Component(obj), m_sprite(nullptr) {
	m_sprite = std::make_shared<sf::Sprite>();
}

void SpriteComponent::Update(float timeDelta) {
	if (m_gameObject.GetPhysicsComponent() != nullptr) m_sprite->setPosition(m_gameObject.GetPhysicsComponent()->GetPosition());
}

void SpriteComponent::SetSprite(int textureID) {
	auto &texture = TextureManager::GetTexture(textureID);
	m_sprite->setTexture(texture);
	m_sprite->setOrigin({ texture.getSize().x / 2.0f, texture.getSize().y / 2.0f });
}

void SpriteComponent::SetSprite(sf::Texture & texture) {
	m_sprite->setTexture(texture);
	m_sprite->setOrigin({ texture.getSize().x / 2.0f, texture.getSize().y / 2.0f });
}

std::shared_ptr<sf::Sprite> SpriteComponent::GetSprite() const {
	return m_sprite;
}

void SpriteComponent::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	if(m_sprite != nullptr) target.draw(*m_sprite);
}
