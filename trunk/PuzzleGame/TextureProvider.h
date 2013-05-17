#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Load.h"

class TextureProvider
{
public:
	static TextureProvider* m_instance;
	static TextureProvider* Instance();

	void Initialize();
	void Cleanup();

	void GetSubRect(sf::Vector2i cellPos, sf::Vector2i cellSize, std::string sheetPath, sf::Sprite* sprite);

	sf::Texture* GetTexture(const std::string &sheetPath);
	std::map<std::string, sf::Texture*> m_textures;

private:
	TextureProvider();
	~TextureProvider();
	sf::Sprite* m_sprite;
};

