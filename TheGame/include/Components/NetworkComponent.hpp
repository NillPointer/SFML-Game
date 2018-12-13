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

	void Connect(sf::IpAddress ip);

	void SetIsHost(bool host);
	bool IsHost();

private:
	sf::TcpSocket m_socket;
	sf::TcpListener m_listener;

	bool m_isHost;
	float m_cooldown;

};

#endif // !NETWORKCOMPONENT_HPP
