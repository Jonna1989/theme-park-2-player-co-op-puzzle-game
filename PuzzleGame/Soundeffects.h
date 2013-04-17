#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ConfigReader.h"

const int NUMBER_OF_UI_SOUNDS = 1;
const std::string SHEET_PATH_TO_SOUND_ASSETS = "Assets/AudioAssets/SoundEffects/UiSound";
const std::string SHEET_PATH_UI_SOUND_1 = (std::string)(SHEET_PATH_TO_SOUND_ASSETS + "1.wav");

class Soundeffects
{
public:
	
	enum SoundCatergory
	{
		UISOUND
	};

	static Soundeffects* Instance();

	void Initialize();
	void Update();
	void Cleanup();

	void PlaySound(int SoundCategory,int SoundNumber);
	void PlaySound(int SoundNumber);
	void StopSound(int SoundNumber);

	void SetSoundvol();



private:
	Soundeffects();
	~Soundeffects();
	

#pragma endregion

	static Soundeffects*	m_instance;

	sf::Sound* m_uiSound;
	std::vector<sf::SoundBuffer*> m_uiBuffers;

#pragma region declare Volume 
	ConfigReader m_soundconfig;
	float m_soundvol;
	bool m_soundon;
#pragma endregion

void CleanupVector(std::vector<sf::Sound*> &vectorToClean);
void PlaySingleSound(sf::Sound* &soundToPlay);
void LoadSoundFile(sf::SoundBuffer* &Buffer, sf::Sound* &Sound, const std::string filename, float initialPitch);
void LoadSoundFile(sf::SoundBuffer* &Buffer, const std::string filename);
void LoadSoundFile(std::vector<sf::SoundBuffer*> &BufferVector, int vectorPosition, const std::string filename);
void SetSoundFromMemory(sf::SoundBuffer* &Buffer, sf::Sound* &Sound, float initialPitch);
void SetBufferToSoundAndPlay(std::vector<sf::SoundBuffer*> VectorToUse, int BufferNumber, sf::Sound* &SoundToUse);

};


