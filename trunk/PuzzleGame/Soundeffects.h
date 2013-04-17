#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ConfigReader.h"

const int NUMBER_OF_UI_SOUNDS = 10;
const std::string SHEET_PATH_TO_SOUND_ASSETS_UI = "Assets/AudioAssets/SoundEffects/UiSounds/UiSound";
const std::string SHEET_PATH_ARRAY_UI[NUMBER_OF_UI_SOUNDS] =
	{
#pragma region Herp
		SHEET_PATH_TO_SOUND_ASSETS_UI+"0.wav",
		SHEET_PATH_TO_SOUND_ASSETS_UI+"1.wav",
		SHEET_PATH_TO_SOUND_ASSETS_UI+"2.wav",
		SHEET_PATH_TO_SOUND_ASSETS_UI+"3.wav",
		SHEET_PATH_TO_SOUND_ASSETS_UI+"4.wav",
		SHEET_PATH_TO_SOUND_ASSETS_UI+"5.wav",
		SHEET_PATH_TO_SOUND_ASSETS_UI+"6.wav",
		SHEET_PATH_TO_SOUND_ASSETS_UI+"7.wav",
		SHEET_PATH_TO_SOUND_ASSETS_UI+"8.wav",
		SHEET_PATH_TO_SOUND_ASSETS_UI+"9.wav"
#pragma endregion
	};

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
void LoadSoundFile(std::vector<sf::SoundBuffer*> &BufferVector, int vectorPosition, const std::string filenameArray[]);
void SetSoundFromMemory(sf::SoundBuffer* &Buffer, sf::Sound* &Sound, float initialPitch);
void SetBufferToSoundAndPlay(std::vector<sf::SoundBuffer*> VectorToUse, int BufferNumber, sf::Sound* &SoundToUse);
};


