#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ConfigReader.h"
#include <stdlib.h>
#include "Load.h"

const std::string PATH_TO_SOUND_EFFECTS = "Assets/AudioAssets/SoundEffects/"; // Path to the 
const int NUMBER_OF_UI_SOUNDS = 7; // Number of sounds in the UISounds folder
const std::string PATH_UI = "UiSounds/UiSound";
const int NUMBER_OF_POP_SOUNDS = 3; // Number of Sounds in the BubblePop folder
const std::string PATH_POP = "BubblePop/Pop";
const int NUMBER_OF_CATEGORIES = 2; // Number of PATHS_

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

	void SetSoundvol();



private:
	Soundeffects();
	~Soundeffects();
	
	std::vector<std::string> m_pathVectorUi;
	std::vector<std::string> m_pathVectorPop;
	static Soundeffects*	m_instance;

	sf::Sound* m_uiSound;
	std::vector<sf::SoundBuffer*> m_uiBuffers;

	sf::Sound* m_popSound;
	std::vector<sf::SoundBuffer*> m_popBuffers;

	std::vector<std::vector<sf::SoundBuffer*>> m_bufferCategories;
	std::vector<sf::Sound*> m_soundCategories;

#pragma region declare Volume 
	ConfigReader m_soundconfig;
	float		 m_soundvol;
	bool		 m_soundon;
#pragma endregion

std::vector<std::string> DeclarePathArray(std::vector<std::string> &m_pathVector, int NumberOfSoundsInArray, const std::string Path); 
void AddVectorsToVector(int numberOfSounds,std::vector<sf::SoundBuffer*> &vectorToLoadInto, std::vector<std::string> &pathVector, sf::Sound* &categorySound);
void CleanupVector(std::vector<sf::SoundBuffer*> &vectorToClean);
void PlaySingleSound(sf::Sound* &soundToPlay);
void LoadSoundFile(sf::SoundBuffer* &Buffer, sf::Sound* &Sound, const std::string filename, float initialPitch);
void LoadSoundFile(sf::SoundBuffer* &Buffer, const std::string filename);
void LoadSoundFile(std::vector<sf::SoundBuffer*> &BufferVector, int vectorPosition, std::vector<std::string> filenameVector);
void SetSoundFromMemory(sf::SoundBuffer* &Buffer, sf::Sound* &Sound, float initialPitch);
void SetBufferToSoundAndPlay(int BufferCategory, int BufferNumber, float Pitch, float Volume);
};


