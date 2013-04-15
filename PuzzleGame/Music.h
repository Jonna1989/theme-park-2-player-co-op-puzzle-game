#pragma once

#include <SFML/Audio.hpp>
#include <iostream>
#include "ConfigReader.h"

class Music
{
public:
	
	enum Track{MenuMusic1,LevelMusic1, PongMusic1};

	static Music* Instance();

	void Initialize	(int TrackNumber);
	void Update();
	//void Cleanup	(int TrackNumber);
	void Cleanup();

// 	void StartMusic	(int Track);
// 	void StopMusic	(int Track);

    void StartMusic	();
    void StopMusic	();

	void IncreasePitch();
	void DecreasePitch();



private:
	Music();
	~Music();
	void SetAllVolume();
	static Music* m_instance;

// 	sf::Music* m_levelMusic1;
// 	sf::Music* m_menuMusic1;

	sf::Music* m_music;

	float pitch;

	ConfigReader m_Soundoptions;
	bool m_musicon;
	float m_musicvol;

	void LoadMusic(sf::Music*& musicToLoad, const std::string filename);
};

