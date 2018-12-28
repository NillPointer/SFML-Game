#ifndef INFLUENCECOMPONENT_HPP
#define INFLUENCECOMPONENT_HPP

#include "game-imap/IMap.h"
#include "Level.hpp"
#include "GameObject.hpp"
#include "Components/Component.hpp"

class InfluenceComponent : public Component {
public:
	InfluenceComponent(GameObject& obj, GameIMap::InfluenceMap& imap, Level& level, float influence = 10, float spreadAmount = 2);

	void Update(float timeDelta);

private:
	GameIMap::InfluenceMap& m_imap;
	Level& m_level;
	float m_influence;
	float m_spreadAmount;
};

#endif // !INFLUENCECOMPONENT_HPP
