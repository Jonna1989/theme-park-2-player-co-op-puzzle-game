#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class TextureProvider
{
public:
	TextureProvider();
	~TextureProvider();
	static TextureProvider* m_instance;
	static TextureProvider* Instance();

	void Initialize();
	void Cleanup();

	sf::Texture* GetTexture(std::string sheetPath); 
	std::map<std::string, sf::Texture*> m_textures;

private:
};

