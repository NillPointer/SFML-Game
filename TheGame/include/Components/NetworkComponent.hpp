#ifndef NETWORKCOMPONENT_HPP
#define NETWORKCOMPONENT_HPP

#include "GameObject.hpp"
#include <SFML/Network.hpp>
#include "Components/Component.hpp"

class Component;

class NetworkComponent : public Component {
public:
	NetworkComponent(GameObject& obj);

	void Update(float timeDelta);

	void SetSocket(sf::TcpSocket& socket);

	void SetIsReceiver(bool receiver);
	bool IsReceiver();

private:
	sf::TcpSocket* m_socket;

	bool m_isReceiver;
	float m_cooldown;

};

#endif // !NETWORKCOMPONENT_HPP
