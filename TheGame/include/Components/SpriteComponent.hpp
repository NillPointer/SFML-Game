#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include <memory>
#include "GameObject.hpp"
#include "Components/Component.hpp"

class Component;

class SpriteComponent: public Component, public sf::Drawable {
public:
	SpriteComponent(GameObject& obj);

	void Update(float timeDelta);

	void SetSprite(int textureID);
	void SetSprite(sf::Texture& texture);
	void SetSpriteTextureRect(sf::IntRect rect);
	sf::IntRect GetSpriteTextureRect() const;
	std::shared_ptr<sf::Sprite> GetSprite() const;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::shared_ptr<sf::Sprite> m_sprite;
};

#endif // !SPRITECOMPONENT_HPP
