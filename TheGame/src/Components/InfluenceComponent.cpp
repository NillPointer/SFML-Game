#include "Components/InfluenceComponent.hpp"

InfluenceComponent::InfluenceComponent(GameObject & obj, GameIMap::InfluenceMap & imap, Level& level, float influence, float spreadAmount):
	Component(obj),
	m_imap(imap),
	m_level(level),
	m_influence(influence),
	m_spreadAmount(spreadAmount)
{}

void InfluenceComponent::Update(float timeDelta) {
	if (!IsActive() || m_gameObject.GetPhysicsComponent() == nullptr) return;
	auto position = m_gameObject.GetPhysicsComponent()->GetPosition();
	Tile* currentTile = m_level.GetTile(position);
	m_imap.setCellValue(currentTile->columnIndex, currentTile->rowIndex, m_influence);
	m_imap.propValue(0.1, GameIMap::PropCurve::Linear);
	m_imap.propagateInfluence(currentTile->columnIndex, currentTile->rowIndex, m_spreadAmount, GameIMap::PropCurve::Linear, 10.0f);
}
