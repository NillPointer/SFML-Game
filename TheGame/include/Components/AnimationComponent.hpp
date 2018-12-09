#ifndef ANIMATIONCOMPONENT_HPP
#define ANIMATIONCOMPONENT_HPP

#include <vector>
#include "Util.hpp"
#include "GameObject.hpp"
#include "Components/Component.hpp"

class Component;

class AnimationComponent: public Component {
public:
	AnimationComponent(GameObject& obj, sf::Texture& texture, int animationSpeed = ANIMATION_SPEED);

	void Update(float timeDelta);

	void AddFrame(sf::IntRect frame);

	sf::Texture& GetTexture() const;

private:
	void NextFrame();

	std::vector<sf::IntRect> m_frames;
	int m_currentFrame;
	float m_animationSpeed;
	float m_progress;
	sf::Texture& m_texure;
};

#endif // !ANIMATIONCOMPONENT_HPP

