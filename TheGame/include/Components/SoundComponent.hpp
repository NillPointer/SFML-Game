#ifndef SOUNDCOMPONENT_HPP
#define SOUNDCOMPONENT_HPP

#include <SFML/Audio.hpp>
#include "GameObject.hpp"
#include "Components/Component.hpp"

class Component;

class SoundComponent : public Component {
public:
	SoundComponent(GameObject& obj, int soundID);
	SoundComponent(GameObject& obj, sf::SoundBuffer& soundBuffer);

	void Update(float timeDelta);

	void AddSound(int soundID);
	void AddSound(sf::SoundBuffer& soundBuffer);

	void PlaySound();

	void SetSoundLooping(bool loop);

private:
	sf::Sound m_sound;
};

#endif // !SOUNDCOMPONENT_HPP

