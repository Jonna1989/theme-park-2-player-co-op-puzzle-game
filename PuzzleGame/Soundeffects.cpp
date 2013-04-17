#include "Soundeffects.h"

#pragma region Base
Soundeffects::Soundeffects()
{
}


Soundeffects::~Soundeffects()
{
}
#pragma endregion

#pragma region Statics

Soundeffects* Soundeffects::m_instance = 0;

Soundeffects* Soundeffects::Instance()
{
	if (m_instance == 0)
	{
		m_instance = new Soundeffects;
	}
	return m_instance;
}

#pragma endregion

#pragma region Publics

#pragma region Initialize
void Soundeffects::Initialize()
{
#pragma region Volume
	if(!m_soundconfig.load("options.txt"))
	{
		std::cout << "Failed to load sound options" << std::endl;
	}
	m_soundvol = m_soundconfig.get("sound_options","soundvolume",m_soundvol) * 10;
	m_soundon = m_soundconfig.get("sound_options","soundon",m_soundon);
#pragma endregion
	for (int i = 0; i < NUMBER_OF_UI_SOUNDS ; i++)
	{
		LoadSoundFile(m_uiBuffers,i,SHEET_PATH_ARRAY_UI);
	}
	m_uiSound = new sf::Sound();
}

#pragma region Update
void Soundeffects::Update()
{
}
#pragma endregion

#pragma region Cleanup
void Soundeffects::Cleanup()
{

}
#pragma endregion

#pragma region PlaySound
void Soundeffects::PlaySound(int SoundNumber)
{
	
}
void Soundeffects::PlaySound(int SoundCategory, int SoundNumber)
{
	switch (SoundCategory)
	{
	case UISOUND:
		SetBufferToSoundAndPlay(m_uiBuffers,SoundNumber,m_uiSound);
			 break;
	}
}
#pragma region StopSound
void Soundeffects::StopSound(int SoundNumber)
{

}

#pragma endregion

#pragma region SetSoundvol
void Soundeffects::SetSoundvol()
{
	m_soundconfig.load("options.txt");
	m_soundon = m_soundconfig.get("sound_options","soundon",m_soundon);
	m_soundvol = m_soundconfig.get("sound_options","soundvolume",m_soundvol) * 10;
	if(m_soundon)
	{
		
	}
	else 
	{
		m_soundvol = 0.0f;
	}
}
#pragma endregion

#pragma endregion

#pragma region Privates
void Soundeffects::CleanupVector(std::vector<sf::Sound*> &vectorToClean)
{
	vectorToClean.clear();
}
void Soundeffects::PlaySingleSound(sf::Sound* &soundToPlay)
{
	if (!soundToPlay->getStatus())
	{
		soundToPlay->play();
	}
}
void Soundeffects::LoadSoundFile(sf::SoundBuffer* &Buffer, sf::Sound* &Sound, const std::string filename, float initialPitch)
{
	Buffer = new sf::SoundBuffer();
	if (Buffer->loadFromFile(filename))
	{
		std::cout << "Loaded sound: " << filename << std::endl;
	}
	else if (!Buffer->loadFromFile(filename))
	{
		std::cout << "Failed to load sound: " << filename << std::endl;
	}
	Sound = new sf::Sound();
	Sound->setBuffer(*Buffer);
	Sound->setPitch(initialPitch);
	Sound->setVolume(m_soundvol);
}
void Soundeffects::LoadSoundFile(std::vector<sf::SoundBuffer*> &BufferVector, int vectorPosition, const std::string filenameArray[])
{
	m_uiBuffers.push_back(new sf::SoundBuffer);
	if (BufferVector[vectorPosition]->loadFromFile(filenameArray[vectorPosition]))
	{
		std::cout << "Loaded sound: " << filenameArray[vectorPosition] << std::endl;
	}
	else if (!BufferVector[vectorPosition]->loadFromFile(filenameArray[vectorPosition]))
	{
		std::cout << "Failed to load sound: " << filenameArray[vectorPosition] << std::endl;
	}
}
void Soundeffects::LoadSoundFile(sf::SoundBuffer* &Buffer, const std::string filename)
{
	Buffer = new sf::SoundBuffer();
	if (Buffer->loadFromFile(filename))
	{
		std::cout << "Loaded soundbuffer: " << filename << std::endl;
	}
	else if (!Buffer->loadFromFile(filename))
	{
		std::cout << "Failed to load soundbuffer: " << filename << std::endl;
	}
}
void Soundeffects::SetSoundFromMemory(sf::SoundBuffer* &Buffer, sf::Sound* &Sound, float initialPitch)
{
	Sound = new sf::Sound();
	Sound->setBuffer(*Buffer);
	Sound->setPitch(initialPitch);
}
void Soundeffects::SetBufferToSoundAndPlay(std::vector<sf::SoundBuffer*> VectorToUse, int BufferNumber,sf::Sound* &SoundToUse)
{
	SoundToUse->stop();
	SoundToUse->setBuffer(*VectorToUse[BufferNumber]);
	SoundToUse->play();
}
#pragma endregion