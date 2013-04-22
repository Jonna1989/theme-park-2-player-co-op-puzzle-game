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
	DeclareSheetPathArray(m_sheetPathVectorUi,NUMBER_OF_UI_SOUNDS,PATH_UI);
	DeclareSheetPathArray(m_sheetPathVectorPop,NUMBER_OF_POP_SOUNDS,PATH_POP);
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
		LoadSoundFile(m_uiBuffers,i,m_sheetPathVectorUi);
	}
	m_uiSound = new sf::Sound();

	for (int i = 0; i < NUMBER_OF_POP_SOUNDS ; i++)
	{
		LoadSoundFile(m_popBuffers,i,m_sheetPathVectorPop);
	}
	m_popSound = new sf::Sound();
}

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
void Soundeffects::PlaySound(int SoundNumber)
{
	
}
void Soundeffects::PlaySound(int SoundCategory, int SoundNumber, float Pitch, float Volume) // The sound category is an enum with all different sound categories
{
	switch (SoundCategory)
	{
	case UISOUND:
		SetBufferToSoundAndPlay(m_uiBuffers,SoundNumber,m_uiSound, Pitch, Volume);
			break;
	case POPSOUND:
		SetBufferToSoundAndPlay(m_popBuffers,SoundNumber,m_popSound, Pitch, Volume);
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

std::vector<std::string> Soundeffects::DeclareSheetPathArray(std::vector<std::string> &m_sheetPathVectorUi, int NumberOfSoundsInArray, const std::string Path)
{
	for (int i = 1; i <= NumberOfSoundsInArray ; i++)
	{
		std::ostringstream	s;
		s << i;
		std::string i_as_string(s.str());
		m_sheetPathVectorUi.push_back(SHEET_PATH_TO_SOUND_EFFECTS+Path+i_as_string+".wav");
	}
	return m_sheetPathVectorUi;
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
void Soundeffects::SetBufferToSoundAndPlay(std::vector<sf::SoundBuffer*> VectorToUse, int BufferNumber,sf::Sound* &SoundToUse, float Pitch, float Volume)
{
	SoundToUse->stop();
	SoundToUse->setBuffer(*VectorToUse[BufferNumber]);
	SoundToUse->setPitch(Pitch);
	SoundToUse->setVolume(Volume);
	SoundToUse->play();
}
#pragma endregion