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
	if(!m_soundconfig.load("Assets/Options/options.txt"))
	{
		std::cout << "Failed to load sound options" << std::endl;
	}
	m_soundvol = m_soundconfig.get("sound_options","soundvolume",m_soundvol) * 10;
	m_soundon = m_soundconfig.get("sound_options","soundon",m_soundon);
#pragma endregion
	AddVectorsToVector(PATH_UI, NUMBER_OF_UI_SOUNDS);
	AddVectorsToVector(PATH_POP, NUMBER_OF_POP_SOUNDS);
	AddVectorsToVector(PATH_DEATH, NUMBER_OF_DEATH_SOUNDS);
	AddVectorsToVector(PATH_SPEEDUP, NUMBER_OF_SPEEDUP_SOUNDS);
	for (int i = 0; i < NUMBER_OF_VECTOR_SOUNDS; i++)
	{
		m_sounds.push_back(new sf::Sound());
	}

}
#pragma endregion

#pragma region Update
void Soundeffects::Update()
{
}
#pragma endregion

#pragma region Cleanup
void Soundeffects::Cleanup()
{
	for (unsigned int i = 0; i < m_sounds.size(); i++)
	{
		delete m_sounds[i];
	}
	for (int i = 0; i < NUMBER_OF_CATEGORIES; i++)
	{
		for (unsigned int k = 0; k < m_buffersAndPaths[i].first.size(); k++)
		{
			delete m_buffersAndPaths[i].first[k];
		}
		m_buffersAndPaths[i].first.clear();
		m_buffersAndPaths[i].second.clear();
	}

}
#pragma endregion

#pragma region PlaySound
void Soundeffects::PlaySound(int SoundCategory, int SoundNumber, float Pitch, float Volume) // The sound category is an enum with all different sound categories
{
	SetBufferToSoundAndPlay(SoundCategory,SoundNumber,Pitch,Volume);
}
#pragma endregion
void Soundeffects::PlayRandomSoundInCategory(int SoundCategory, int lowRange, int highRange)
{
	SetBufferToSoundAndPlay(SoundCategory,RandomNumber(lowRange,highRange),1,50);
}
#pragma region SetSoundvol
void Soundeffects::SetSoundvol()
{
	m_soundconfig.load("options.txt");
	m_soundon = m_soundconfig.get("sound_options","soundon",m_soundon);
	m_soundvol = m_soundconfig.get("sound_options","soundvolume",m_soundvol) * 10;
	if(!m_soundon)
	{
		m_soundvol = 0.0f;
	}
}
#pragma endregion

#pragma region Privates
void Soundeffects::AddVectorsToVector(const std::string &path, int numberOfSounds)
{
	std::vector<sf::SoundBuffer*> bufferVectorToAddToVectorBufferVector;
	std::vector<std::string> pathVectorToAddToVectorPathVector;
	for (int i = 0; i < numberOfSounds; i++)
	{
		pathVectorToAddToVectorPathVector.push_back(PATH_TO_SOUND_EFFECTS+path+ConvertIntToStdString(i+1)+".wav");
		LoadSoundFile(bufferVectorToAddToVectorBufferVector,i,pathVectorToAddToVectorPathVector);
	}
	m_buffersAndPaths.push_back(std::pair< std::vector<sf::SoundBuffer*>,std::vector<std::string>>(bufferVectorToAddToVectorBufferVector,pathVectorToAddToVectorPathVector));
}
void Soundeffects::LoadSoundFile(sf::SoundBuffer* &Buffer, sf::Sound* &Sound, const std::string &filename, float initialPitch)
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
void Soundeffects::LoadSoundFile(std::vector<sf::SoundBuffer*> &BufferVector, int vectorPosition, std::vector<std::string> filenameVector)
{
	BufferVector.push_back(new sf::SoundBuffer);
	if (BufferVector[vectorPosition]->loadFromFile(filenameVector[vectorPosition]))
	{
		std::cout << "Loaded sound: " << filenameVector[vectorPosition] << std::endl;
	}
	else if (!BufferVector[vectorPosition]->loadFromFile(filenameVector[vectorPosition]))
	{
		std::cout << "Failed to load sound: " << filenameVector[vectorPosition] << std::endl;
	}
}
void Soundeffects::LoadSoundFile(sf::SoundBuffer* &Buffer, const std::string &filename)
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
void Soundeffects::SetBufferToSoundAndPlay(int BufferCategory, int BufferNumber, float Pitch, float Volume)
{

	unsigned int temp = m_sounds.size();
	for (unsigned int i = 0; i < temp; i++)
	{
		if (!(m_sounds[i]->getStatus() == sf::Sound::Playing))
		{
			m_sounds[i]->setBuffer(*m_buffersAndPaths[BufferCategory].first[BufferNumber]);
			m_sounds[i]->setPitch(Pitch);
			m_sounds[i]->setVolume(Volume);
			m_sounds[i]->play();
			break;
		}
		if (i == temp)
		{
			i = 0;
		}
	}
}
#pragma endregion