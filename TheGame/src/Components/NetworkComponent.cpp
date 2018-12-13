#include "Components/NetworkComponent.hpp"

NetworkComponent::NetworkComponent(GameObject & obj): 
	Component(obj),
	m_cooldown(0),
	m_isHost(false)
{
	m_socket.setBlocking(false);
}

void NetworkComponent::Update(float timeDelta) {
	if (!IsActive()) return;

	if (m_gameObject.GetPhysicsComponent() == nullptr) return;
	sf::Packet m_hostPacket;
	if (m_isHost) {
		auto position = m_gameObject.GetPhysicsComponent()->GetPosition();
		m_hostPacket << position.x << position.y;
		std::cout << "SENT FROM HOST: " << position.x << ", " << position.y << std::endl;
		m_socket.send(m_hostPacket);
	} else {
		auto currentPos = m_gameObject.GetPhysicsComponent()->GetPosition();
		if (m_socket.receive(m_hostPacket) == sf::Socket::Done) {
			m_hostPacket >> currentPos.x >> currentPos.y;
			std::cout << "RECEIVED FROM HOST: " << currentPos.x << ", " << currentPos.y << std::endl;
			m_gameObject.GetPhysicsComponent()->SetPosition(currentPos);
		}
	}

#if 0
	if (m_isHost) {
		if (m_gameObject.GetInputComponent() != nullptr) {
			auto position = m_gameObject.GetPhysicsComponent()->GetPosition();
			m_hostPacket << position.x << position.y;
			std::cout << "SENT FROM HOST: " << position.x << ", " << position.y << std::endl;
			m_socket.send(m_hostPacket);
		} else {
			auto currentPos = m_gameObject.GetPhysicsComponent()->GetPosition();
			if (m_socket.receive(m_clientPacket) == sf::Socket::Done) {
				m_clientPacket >> currentPos.x >> currentPos.y;
				std::cout << "RECEIVED FROM CLIENT: " << currentPos.x << ", " << currentPos.y << std::endl;
				m_gameObject.GetPhysicsComponent()->SetPosition(currentPos);
			}
		}
	} else {
		if (m_gameObject.GetInputComponent() == nullptr) {
			auto currentPos = m_gameObject.GetPhysicsComponent()->GetPosition();
			if (m_socket.receive(m_hostPacket) == sf::Socket::Done) {
				m_hostPacket >> currentPos.x >> currentPos.y;
				std::cout << "RECEIVED FROM HOST: " << currentPos.x << ", " << currentPos.y << std::endl;
				m_gameObject.GetPhysicsComponent()->SetPosition(currentPos);
			}
		} else {
			auto position = m_gameObject.GetPhysicsComponent()->GetPosition();
			m_clientPacket << position.x << position.y;
			std::cout << "SENT FROM CLIENT: " << position.x << ", " << position.y << std::endl;
			m_socket.send(m_clientPacket);
		}
	}
#endif
}

void NetworkComponent::Connect(sf::IpAddress ip) {
	if (!m_isHost) {
		std::cout << " CLIENT!!!! \n" << std::endl;
		sf::Socket::Status status = m_socket.connect(ip, 55001);
		if (status != sf::Socket::Done) {
			std::cout << "ERROR HAS OCCURED WHILE CLIENT TRIED TO CONNECT TO HOST!" << std::endl;
			return;
		}
	} else {
		std::cout << " HOST!!!! \n" << std::endl;
		if (m_listener.listen(55001) != sf::Socket::Done) {
			std::cout << "ERROR HAS OCCURED WHILE HOST WAS LISTENING FOR CLIENT!" << std::endl;
			return;
		}
		if (m_listener.accept(m_socket) != sf::Socket::Done) {
			std::cout << "ERROR HAS OCCURED WHILE HOST WAS ACCEPTING CLIENT!" << std::endl;
			return;
		}
	}
}

void NetworkComponent::SetIsHost(bool host) {
	m_isHost = host;
}

bool NetworkComponent::IsHost() {
	return m_isHost;
}
