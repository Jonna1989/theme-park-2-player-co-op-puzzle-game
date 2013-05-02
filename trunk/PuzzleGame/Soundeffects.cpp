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

	DeclarePathArray(m_pathVectorUi,NUMBER_OF_UI_SOUNDS,PATH_UI);
	DeclarePathArray(m_pathVectorPop,NUMBER_OF_POP_SOUNDS,PATH_POP);

	AddVectorsToVector(NUMBER_OF_UI_SOUNDS,m_uiBuffers,m_pathVectorUi,m_uiSound);
	AddVectorsToVector(NUMBER_OF_POP_SOUNDS,m_popBuffers,m_pathVectorPop,m_popSound);
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
	delete m_uiSound;
	CleanupVector(m_uiBuffers);
	delete m_popSound;
	CleanupVector(m_popBuffers);
}
#pragma endregion

#pragma region PlaySound
void Soundeffects::PlaySound(int SoundCategory, int SoundNumber, float Pitch, float Volume) // The sound category is an enum with all different sound categories
{
	SetBufferToSoundAndPlay(SoundCategory,SoundNumber,Pitch,Volume);
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

#pragma region Privates

std::vector<std::string> Soundeffects::DeclarePathArray(std::vector<std::string> &m_pathVector, int NumberOfSoundsInArray, const std::string path)
{
	for (int i = 1; i <= NumberOfSoundsInArray ; i++)
	{
		m_pathVector.push_back(PATH_TO_SOUND_EFFECTS+path+ConvertIntToStdString(i)+".wav");
	}
	return m_pathVector;
}
void Soundeffects::AddVectorsToVector(int numberOfSounds,std::vector<sf::SoundBuffer*> &vectorToLoadInto, std::vector<std::string> &pathVector, sf::Sound* &categorySound)
{
	for (int i = 0; i < numberOfSounds; i++)
	{
		LoadSoundFile(vectorToLoadInto,i,pathVector);
	}
	m_bufferCategories.push_back(vectorToLoadInto);
	categorySound = new sf::Sound();
	m_soundCategories.push_back(categorySound);
}
void Soundeffects::CleanupVector(std::vector<sf::SoundBuffer*> &vectorToClean)
{
	for (unsigned int i = 0; i < vectorToClean.size() ; i++)
	{
		delete vectorToClean[i];
	}
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
void Soundeffects::SetBufferToSoundAndPlay(int BufferCategory, int BufferNumber, float Pitch, float Volume)
{
	m_soundCategories[BufferCategory]->stop();
	m_soundCategories[BufferCategory]->setBuffer(*m_bufferCategories[BufferCategory][BufferNumber]);
	m_soundCategories[BufferCategory]->setPitch(Pitch);
	m_soundCategories[BufferCategory]->setVolume(Volume);
	m_soundCategories[BufferCategory]->play();
}
#pragma endregion