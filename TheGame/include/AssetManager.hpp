//-------------------------------------------------------------------------------------
// AssetManager.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AssetManager {
public:
	/**
	 * Default constructor.
	 */
	AssetManager();

	/**
	 * Adds a texture to the manager and returns its id in the map.
	 * @param The path to the image to load.
	 * @return The id to the texture created, or the id in the map if it already exists.
	 */
	static int AddTexture(std::string filePath);

	/**
	* Add a soundbuffer to the manager and returns its id in the map.
	* @param The path to the sound to load.
	* @return The id to the soundbuffer created, or the id in the map if it already exists.
	*/
	static int AddSoundBuffer(std::string filePath);

	/**
	 * Removes a texture from the manager from a given id.
	 * @param textureID The id of the texture to be removed.
	 */
	static void RemoveTexture(int textureID);

	/**
	* Removes a soundbuffer from the manager from a given id.
	* @param soundID The id of the soundbuffer to be removed.
	*/
	static void RemoveSoundBuffer(int soundID);

	/**
	 * Gets a texture from the texture manager from an ID.
	 * @param textureId The id of the texture to return.
	 * @return A const reference to the texture.
	*/
	static sf::Texture& GetTexture(int textureId);

	/**
	* Gets a soundbuffer from the asset manager from an ID.
	* @param soundID The id of the sound to return.
	* @return A const reference to the soundbuffer.
	*/
	static sf::SoundBuffer& GetSoundBuffer(int soundID);

private:
	/**
	 * A map of each texture name with its ID.
	 */
	static std::map<std::string, std::pair<int, std::unique_ptr<sf::Texture>>> m_textures;

	/**
	* A map of each soundbuffer name with its ID.
	*/
	static std::map<std::string, std::pair<int, std::unique_ptr<sf::SoundBuffer>>> m_soundBuffers;

	/**
	 * The current texture key value.
	 */
	static int m_currentTextureId;

	/**
	* The current soundbuffer key value.
	*/
	static int m_currentSoundId;
};
#endif