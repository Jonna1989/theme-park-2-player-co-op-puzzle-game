#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ConfigReader.h"
#include <sstream>
#include <stdlib.h>

const std::string SHEET_PATH_TO_SOUND_EFFECTS = "Assets/AudioAssets/SoundEffects/";
const int NUMBER_OF_UI_SOUNDS = 7;
const std::string PATH_UI = "UiSounds/UiSound";
const int NUMBER_OF_POP_SOUNDS = 1;
const std::string PATH_POP = "BubblePop/Pop";
const float DEFAULT_PITCH = 1.0f;

class Soundeffects
{
public:
	
	enum SoundCatergory
	{
		UISOUND,
		POPSOUND
	};

	static Soundeffects* Instance();

	void Initialize();
	void Update();
	void Cleanup();

	void PlaySound(int SoundCategory,int SoundNumber, float Pitch, float Volume);
	void PlaySound(int SoundNumber);
	void StopSound(int SoundNumber);

	void SetSoundvol();



private:
	Soundeffects();
	~Soundeffects();
	
	std::vector<std::string> m_sheetPathVectorUi;
	std::vector<std::string> m_sheetPathVectorPop;
	static Soundeffects*	m_instance;

	sf::Sound* m_uiSound;
	std::vector<sf::SoundBuffer*> m_uiBuffers;

	sf::Sound* m_popSound;
	std::vector<sf::SoundBuffer*> m_popBuffers;

#pragma region declare Volume 
	ConfigReader m_soundconfig;
	float m_soundvol;
	bool m_soundon;
#pragma endregion

std::vector<std::string> DeclareSheetPathArray(std::vector<std::string> &m_sheetPathVectorUi, int NumberOfSoundsInArray, const std::string Path); 

void CleanupVector(std::vector<sf::SoundBuffer*> &vectorToClean);
void PlaySingleSound(sf::Sound* &soundToPlay);
void LoadSoundFile(sf::SoundBuffer* &Buffer, sf::Sound* &Sound, const std::string filename, float initialPitch);
void LoadSoundFile(sf::SoundBuffer* &Buffer, const std::string filename);
void LoadSoundFile(std::vector<sf::SoundBuffer*> &BufferVector, int vectorPosition, std::vector<std::string> filenameVector);
void SetSoundFromMemory(sf::SoundBuffer* &Buffer, sf::Sound* &Sound, float initialPitch);
void SetBufferToSoundAndPlay(std::vector<sf::SoundBuffer*> VectorToUse, int BufferNumber, sf::Sound* &SoundToUse, float Pitch, float Volume);
};


