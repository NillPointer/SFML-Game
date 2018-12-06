#include "Components/GraphicsComponent.hpp"
#include "TextureManager.hpp"

GraphicsComponent::GraphicsComponent() :
m_animationSpeed(0),
m_isAnimated(false),
m_frameCount(0),
m_currentFrame(0),
m_frameWidth(0),
m_frameHeight(0),
m_timeDelta(0) {}

void GraphicsComponent::Update(GameObject& obj, float timeDelta) {
	m_timeDelta += timeDelta;
}

void GraphicsComponent::Draw(sf::RenderTarget& target) {
	if (m_isAnimated) {
		if (m_timeDelta >= (1.0f / m_animationSpeed)) {
			NextFrame();
			m_timeDelta = 0;
		}
	}

	target.draw(m_sprite);
}

bool GraphicsComponent::SetSprite(sf::Texture& texture, bool isSmooth, int frames, int frameSpeed) {
	m_sprite.setTexture(texture);
	m_animationSpeed = frameSpeed;
	m_frameCount = frames;

	sf::Vector2u texSize = m_sprite.getTexture()->getSize();
	m_frameWidth = texSize.x / m_frameCount;
	m_frameHeight = texSize.y;

	if (frames > 1) {
		m_isAnimated = true;
		m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
	} else m_isAnimated = false;

	m_sprite.setOrigin(m_frameWidth / 2.f, m_frameHeight / 2.f);

	return true;
}

void GraphicsComponent::NextFrame() {
	if (m_currentFrame == (m_frameCount - 1)) m_currentFrame = 0;
	else m_currentFrame++;
	m_sprite.setTextureRect(sf::IntRect(m_frameWidth * m_currentFrame, 0, m_frameWidth, m_frameHeight));
}

sf::Sprite& GraphicsComponent::GetSprite() { return m_sprite; }

int GraphicsComponent::GetFrameCount() const { return m_frameCount; }

bool GraphicsComponent::IsAnimated() { return m_isAnimated; }

int(&GraphicsComponent::GetTextureIDs())[static_cast<int>(ANIMATION_STATE::COUNT)] { return m_textureIDs; }

int& GraphicsComponent::GetCurrenTextureIndex() { return m_currentTextureIndex; }

void GraphicsComponent::SetAnimated(bool isAnimated) { 
	m_isAnimated = isAnimated;

	if (isAnimated) m_currentFrame = 0;
	else m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
}



/* Player Graphics Component */

PlayerGraphicsComponent::PlayerGraphicsComponent(std::string className): GraphicsComponent() {
	// Load textures.
	auto texturePathPrefix = "resource/players/" + className + "/spr_" + className;
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture(texturePathPrefix + "_walk_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture(texturePathPrefix + "_walk_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture(texturePathPrefix + "_walk_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture(texturePathPrefix + "_walk_left.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture(texturePathPrefix + "_idle_up.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture(texturePathPrefix + "_idle_down.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture(texturePathPrefix + "_idle_right.png");
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture(texturePathPrefix + "_idle_left.png");

	// Set initial sprite.
	SetSprite(TextureManager::GetTexture(m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)]), false, 8, 12);
	m_currentTextureIndex = static_cast<int>(ANIMATION_STATE::WALK_UP);
	m_sprite.setOrigin(sf::Vector2f(13.f, 18.f));
}

void PlayerGraphicsComponent::Update(GameObject& obj, float timeDelta) {
	GraphicsComponent::Update(obj, timeDelta);

	if (m_currentTextureIndex != static_cast<int>(m_animState)) {
		m_currentTextureIndex = static_cast<int>(m_animState);
		m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
	}

	if (obj.GetPhysicsComponent() == nullptr) return;

	sf::Vector2f movement = obj.GetPhysicsComponent()->GetVelocity();
	if (movement.x == 0 && movement.y == 0) {
		if (IsAnimated()) {
			m_currentTextureIndex += 4;
			m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
			SetAnimated(false);
		}
	} else {
		if (!IsAnimated()) {
			m_currentTextureIndex -= 4;
			m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
			SetAnimated(true);
		}
	}
}

void PlayerGraphicsComponent::SetAnimationState(ANIMATION_STATE state) {
	m_animState = state;
}