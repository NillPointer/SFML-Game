#ifndef GraphicsComponent_hpp
#define GraphicsComponent_hpp

#include "GameObject.hpp"
#include "Enums.hpp"

class GameObject;

class GraphicsComponent {
public:
	GraphicsComponent();
	virtual ~GraphicsComponent() {};
	virtual void Update(GameObject& obj, float timeDelta);
	virtual void Draw(sf::RenderTarget& target);
	virtual void SetAnimationState(ANIMATION_STATE state) = 0;

	bool SetSprite(sf::Texture& texture, bool isSmooth, int frames = 1, int frameSpeed = 0);
	sf::Sprite& GetSprite();
	int GetFrameCount() const;
	bool IsAnimated();
	void SetAnimated(bool isAnimated);
	int(&GetTextureIDs())[static_cast<int>(ANIMATION_STATE::COUNT)];
	int& GetCurrenTextureIndex();

	float m_timeDelta;
	
protected:

	sf::Sprite m_sprite;
	int m_textureIDs[static_cast<int>(ANIMATION_STATE::COUNT)];
	int m_currentTextureIndex;

private:
	void NextFrame();

	int m_animationSpeed;
	bool m_isAnimated;
	int m_frameCount;
	int m_currentFrame;
	int m_frameWidth;
	int m_frameHeight;
};

class PlayerGraphicsComponent : public GraphicsComponent {
public:
	PlayerGraphicsComponent(std::string className);
	virtual void Update(GameObject& obj, float timeDelta);

	void SetAnimationState(ANIMATION_STATE state);
	ANIMATION_STATE GetAnimationState() { return m_animState; }

private:
	ANIMATION_STATE m_animState = ANIMATION_STATE::WALK_UP;
};

#endif // !GraphicsComponent_hpp
