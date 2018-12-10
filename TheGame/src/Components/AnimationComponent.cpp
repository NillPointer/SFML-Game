#include "Components/AnimationComponent.hpp"
#include "TextureManager.hpp"

AnimationComponent::AnimationComponent(GameObject & obj, sf::Texture & texture, int animationSpeed):
	Component(obj),
	m_texure(texture),
	m_animationSpeed(animationSpeed),
	m_progress(0),
	m_currentFrame(0)
{}

void AnimationComponent::Update(float timeDelta) {
	if (!IsActive()) return;

	m_progress += timeDelta;

	if (m_progress >= (1.0f / m_animationSpeed)) {
		m_progress = 0;
		NextFrame();
	}

	if (m_gameObject.GetSpriteComponent() != nullptr) {
		auto spritecmp = m_gameObject.GetSpriteComponent();
		if (spritecmp->GetSprite()->getTexture() != &m_texure) spritecmp->SetSprite(m_texure);
	}
}

void AnimationComponent::NextFrame() {
	m_currentFrame = (m_currentFrame + 1) % m_frames.size();
	if (m_gameObject.GetSpriteComponent() != nullptr) {
		m_gameObject.GetSpriteComponent()->SetSpriteTextureRect(m_frames[m_currentFrame]);
	}
}

void AnimationComponent::AddFrame(sf::IntRect frame) {
	m_frames.push_back(frame);
}

sf::Texture& AnimationComponent::GetTexture() const {
	return m_texure;
}