#include "Components/AnimatorComponent.hpp"
#include "TextureManager.hpp"

AnimatorComponent::AnimatorComponent(GameObject & obj): Component(obj), m_currentAnimation(0){}

void AnimatorComponent::Update(float timeDelta) {
	if (m_animations.find(m_currentAnimation) != m_animations.end()) m_animations[m_currentAnimation]->Update(timeDelta);

	if (m_gameObject.GetPhysicsComponent() == nullptr) return;
	auto velocity = m_gameObject.GetPhysicsComponent()->GetVelocity();
	if (velocity.x == 0 && velocity.y == 0) { if (m_animations.size() >= 7 && m_currentAnimation < 4) m_currentAnimation += 4; }
	else { if (m_animations.size() >= 7 && m_currentAnimation >= 4) m_currentAnimation -= 4; }
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
