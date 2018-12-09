#include "Components/AnimatorComponent.hpp"
#include "TextureManager.hpp"

AnimatorComponent::AnimatorComponent(GameObject & obj): Component(obj), m_currentAnimation(0){}

void AnimatorComponent::Update(float timeDelta) {
	if (m_animations.find(m_currentAnimation) != m_animations.end()) m_animations[m_currentAnimation]->Update(timeDelta);
}

void AnimatorComponent::AddAnimation(int animationID, int textureID) {
	m_animations.insert(std::make_pair(animationID, std::make_shared<AnimationComponent>(m_gameObject, TextureManager::GetTexture(textureID))));
}

void AnimatorComponent::AddAnimation(int animationID, sf::Texture& texture) {
	m_animations.insert(std::make_pair(animationID, std::make_shared<AnimationComponent>(m_gameObject, texture)));
}

void AnimatorComponent::AddAnimation(int animationID, std::shared_ptr<AnimationComponent> animation) {
	m_animations.insert(std::make_pair(animationID, animation));
}

void AnimatorComponent::SetCurrentAnimation(int animationID) {
	m_currentAnimation = animationID;
}

int AnimatorComponent::GetCurrentAnimation() {
	return m_currentAnimation;
}

AnimationComponent& AnimatorComponent::GetAnimation(int animationID) {
	if (m_animations.find(animationID) != m_animations.end()) return *m_animations[animationID];
}
