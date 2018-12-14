#include "Components/NetworkComponent.hpp"

NetworkComponent::NetworkComponent(GameObject & obj): 
	Component(obj),
	m_cooldown(0),
	m_socket(nullptr)
{
}

void NetworkComponent::Update(float timeDelta) {
	if (!IsActive()) return;
	if (m_gameObject.GetPhysicsComponent() == nullptr) return;

	sf::Packet packet;
	if (m_isReceiver) {
		auto velocity = m_gameObject.GetPhysicsComponent()->GetVelocity();
		int animation = 5;
		if (m_socket->receive(packet) == sf::Socket::Done) {
			packet >> velocity.x >> velocity.y >> animation;
			m_gameObject.GetPhysicsComponent()->SetVelocity(velocity);
			if (m_gameObject.GetAnimatorComponent() != nullptr) m_gameObject.GetAnimatorComponent()->SetCurrentAnimation(animation);
		}
	} else {
		auto velocity = m_gameObject.GetPhysicsComponent()->GetVelocity();
		int animation = 5;
		if (m_gameObject.GetAnimatorComponent() != nullptr) animation = m_gameObject.GetAnimatorComponent()->GetCurrentAnimation();
		packet << velocity.x << velocity.y << animation;
		m_socket->send(packet);
	}
}

void NetworkComponent::SetSocket(sf::TcpSocket& socket) {
	m_socket = &socket;
}

void NetworkComponent::SetIsReceiver(bool receiver) {
	m_isReceiver = receiver;
}

bool NetworkComponent::IsReceiver() {
	return m_isReceiver;
}
