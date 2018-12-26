#include "Components/NetworkComponent.hpp"

NetworkComponent::NetworkComponent(GameObject & obj): 
	Component(obj),
	m_cooldown(0),
	m_socket(nullptr)
{
}

void NetworkComponent::Update(float timeDelta) {
	if (!IsActive() || m_socket == nullptr) return;
	if (m_gameObject.GetPhysicsComponent() == nullptr) return;

	std::cout << "Networking" << std::endl;

	sf::Packet packet;
	if (m_isReceiver) {
		auto position = m_gameObject.GetPhysicsComponent()->GetPosition();
		int animation = 5;
		if (m_socket->receive(packet) == sf::Socket::Done) {
			packet >> position.x >> position.y >> animation;
			m_gameObject.GetPhysicsComponent()->SetPosition(position);
			if (m_gameObject.GetAnimatorComponent() != nullptr) m_gameObject.GetAnimatorComponent()->SetCurrentAnimation(animation);
		}
	} else {
		auto position = m_gameObject.GetPhysicsComponent()->GetPosition();
		int animation = 5;
		if (m_gameObject.GetAnimatorComponent() != nullptr) animation = m_gameObject.GetAnimatorComponent()->GetCurrentAnimation();
		packet << position.x << position.y << animation;
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
