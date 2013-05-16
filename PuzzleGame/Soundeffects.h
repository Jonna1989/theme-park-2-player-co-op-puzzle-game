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
const int NUMBER_OF_DEATH_SOUNDS = 1;
const std::string PATH_DEATH = "DeathSounds/DeathSound";
const int NUMBER_OF_SPEEDUP_SOUNDS = 5;
const std::string PATH_SPEEDUP = "SpeedupSounds/speedup";
const int NUMBER_OF_CATEGORIES = 4; // Number of PATHS_

#define PlayRotateSound Soundeffects::Instance()->PlaySound(Soundeffects::UISOUND,4,DEFAULT_PITCH,35);

const float DEFAULT_PITCH = 1.0f;

const int NUMBER_OF_VECTOR_SOUNDS = 20;

class Soundeffects
{
public:
	
	enum SoundCatergory
	{
		UISOUND,
		POPSOUND,
		DEATHSOUND,
		SPEEDUPSOUND
	};

	static Soundeffects* Instance();

	void Initialize();
	void Update();
	void Cleanup();

	void PlaySound(int SoundCategory,int SoundNumber, float Pitch, float Volume);
	void PlayRandomSoundInCategory(int SoundCategory, int lowRange, int highRange);
	void SetSoundvol();



private:
	Soundeffects();
	~Soundeffects();
	static Soundeffects*	m_instance;

	std::vector<std::pair< std::vector<sf::SoundBuffer*>,std::vector<std::string>>> m_buffersAndPaths;
	std::vector<sf::Sound*> m_sounds;

#pragma region declare Volume 
	ConfigReader m_soundconfig;
	float		 m_soundvol;
	bool		 m_soundon;
#pragma endregion

void AddVectorsToVector(const std::string path, int numberOfSounds);
void CleanupVector(std::vector<sf::SoundBuffer*> &vectorToClean);
void PlaySingleSound(sf::Sound* &soundToPlay);
void LoadSoundFile(sf::SoundBuffer* &Buffer, sf::Sound* &Sound, const std::string filename, float initialPitch);
void LoadSoundFile(sf::SoundBuffer* &Buffer, const std::string filename);
void LoadSoundFile(std::vector<sf::SoundBuffer*> &BufferVector, int vectorPosition, std::vector<std::string> filenameVector);
void SetSoundFromMemory(sf::SoundBuffer* &Buffer, sf::Sound* &Sound, float initialPitch);
void SetBufferToSoundAndPlay(int BufferCategory, int BufferNumber, float Pitch, float Volume);
};


