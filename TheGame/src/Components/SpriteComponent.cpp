#include "Components/SpriteComponent.hpp"
#include "TextureManager.hpp"

SpriteComponent::SpriteComponent(GameObject & obj) : Component(obj), m_sprite(nullptr) {
	m_sprite = std::make_shared<sf::Sprite>();
}

void SpriteComponent::Update(float timeDelta) {
	if (!IsActive()) return;
	if (m_gameObject.GetPhysicsComponent() != nullptr) m_sprite->setPosition(m_gameObject.GetPhysicsComponent()->GetPosition());
}

void SpriteComponent::SetSprite(int textureID) {
	auto &texture = TextureManager::GetTexture(textureID);
	m_sprite->setTexture(texture);
	m_sprite->setOrigin({ texture.getSize().x / 2.0f, texture.getSize().y / 2.0f });
}

void SpriteComponent::SetSprite(sf::Texture & texture) {
	m_sprite->setTexture(texture);
}

void SpriteComponent::SetSpriteTextureRect(sf::IntRect rect) {
	m_sprite->setTextureRect(rect);
	m_sprite->setOrigin({ rect.width / 2.0f, rect.height / 2.0f });
}

sf::IntRect SpriteComponent::GetSpriteTextureRect() const {
	return m_sprite->getTextureRect();
}

std::shared_ptr<sf::Sprite> SpriteComponent::GetSprite() const {
	return m_sprite;
}

void SpriteComponent::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	if (!IsActive()) return;
	if(m_sprite != nullptr) target.draw(*m_sprite);
}
