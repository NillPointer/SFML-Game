#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include "Component.hpp"

class SpriteComponent: public Component {
public:
	SpriteComponent(GameObject& obj);

	void Update(float timeDelta);
};

#endif // !SPRITECOMPONENT_HPP
