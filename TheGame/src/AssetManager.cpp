#include "AssetManager.hpp"

std::map<std::string, std::pair<int, std::unique_ptr<sf::Texture>>> AssetManager::m_textures;
int AssetManager::m_currentTextureId = 0;

std::map<std::string, std::pair<int, std::unique_ptr<sf::SoundBuffer>>> AssetManager::m_soundBuffers;
int AssetManager::m_currentSoundId = 0;

// Default Constructor.
AssetManager::AssetManager() {
}

// Adds a texture to the manager, and returns its id in the map.
int AssetManager::AddTexture(std::string filePath) {
	// First check if the texture has already been created. If so, simply return that one.
	auto it = m_textures.find(filePath);

	if (it != m_textures.end()) return it->second.first;

	// At this point the texture doesn't exists, so we'll create and add it.
	m_currentTextureId++;

	std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
	if (!texture->loadFromFile(filePath)) return -1;

	m_textures.insert(std::make_pair(filePath, std::make_pair(m_currentTextureId, std::move(texture))));

	// Return the texture.
	return m_currentTextureId;
}

// Removes a texture from the manager from a given id.
void AssetManager::RemoveTexture(int textureID) {
	for (auto it = m_textures.begin(); it != m_textures.end(); ++it){
		if (it->second.first == textureID) m_textures.erase(it->first);
	}
}

// Gets a texture from the texture manager from an ID.
sf::Texture& AssetManager::GetTexture(int textureID) {
	for (auto it = m_textures.begin(); it != m_textures.end(); ++it) {
		if (it->second.first == textureID) return *it->second.second;
	}
}

// Adds a sound to the manager, and returns its id in the map.
int AssetManager::AddSoundBuffer(std::string filePath) {
	// First check if the sound has already been created. If so, simply return that one.
	auto it = m_soundBuffers.find(filePath);

	if (it != m_soundBuffers.end()) return it->second.first;

	// At this point the soundbuffer doesn't exists, so we'll create and add it.
	m_currentSoundId++;

	std::unique_ptr<sf::SoundBuffer> soundBuffer = std::make_unique<sf::SoundBuffer>();
	if (!soundBuffer->loadFromFile(filePath)) return -1;

	m_soundBuffers.insert(std::make_pair(filePath, std::make_pair(m_currentSoundId, std::move(soundBuffer))));

	// Return the soundbuffer.
	return m_currentSoundId;
}

// Removes a soundbuffer from the manager from a given id.
void AssetManager::RemoveSoundBuffer(int soundID) {
	for (auto it = m_soundBuffers.begin(); it != m_soundBuffers.end(); ++it) {
		if (it->second.first == soundID) m_soundBuffers.erase(it->first);
	}
}

// Gets a soudnbuffer from the manager from an ID.
sf::SoundBuffer& AssetManager::GetSoundBuffer(int soundID) {
	for (auto it = m_soundBuffers.begin(); it != m_soundBuffers.end(); ++it) {
		if (it->second.first == soundID) return *it->second.second;
	}
}