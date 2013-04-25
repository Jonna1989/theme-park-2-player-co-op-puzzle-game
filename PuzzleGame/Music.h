#pragma once

#include <SFML/Audio.hpp>
#include <iostream>
#include "ConfigReader.h"

const float PITCH_SPEED = 0.5f;

class Music
{
public:
	
	enum Track{MenuMusic1,LevelMusic1};

	static Music* Instance();

	void Initialize	(int TrackNumber);
	void Update();
	void Cleanup();

    void StartMusic	();
    void StopMusic	();

	void IncreasePitch();
	void DecreasePitch();

	sf::Music* GetMusic();
	void ResetPitchVariable();
	float GetPitchVariable();

private:
	Music();
	~Music();
	void SetAllVolume();
	static Music* m_instance;

	sf::Music* m_music;

	float pitch;

	ConfigReader m_Soundoptions;
	bool m_musicon;
	float m_musicvol;

	void LoadMusic(sf::Music*& musicToLoad, const std::string filename);
};

