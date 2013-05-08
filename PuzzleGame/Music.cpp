#include "Music.h"
#include "InputManager.h"
#pragma region Base
Music::Music()
{
}
Music::~Music()
{
}
#pragma endregion

#pragma region Statics

Music* Music::m_instance = 0;

Music* Music::Instance()
{
	if (m_instance == 0)
	{
		m_instance = new Music;
	}
	return m_instance;
}

#pragma endregion

#pragma region Publics
#pragma region Initialize
void Music::Initialize(int TrackNumber)
{
	
	if(!m_Soundoptions.load("Assets/Options/options.txt"))
	{
		std::cout << "Failed to load music options" << std::endl;
	}
	m_musicon = m_Soundoptions.get("sound_options","musicon",m_musicon);
	m_musicvol = m_Soundoptions.get("sound_options","musicvolume",m_musicvol) * 10.0f;

	switch (TrackNumber)
	{
	case MenuMusic1:
		LoadMusic(m_music,"Assets/AudioAssets/Music/can.ogg");
		break;
	case LevelMusic1:
		LoadMusic(m_music,"Assets/AudioAssets/Music/chicken.ogg");
		break;
	case GameOverMusic1:
		LoadMusic(m_music,"Assets/AudioAssets/Music/canLose.ogg");
		break;
	}

	pitch = 1;
}
#pragma endregion
#pragma region Update
void Music::Update()
{
	SetAllVolume();
}
#pragma endregion
#pragma region Cleanup
void Music::Cleanup()
{
	delete m_music;
}
#pragma endregion

#pragma region OnOff
void Music::StartMusic()
{
	m_music->play();
}
void Music::StopMusic()
{
	m_music->stop();
}
#pragma endregion

#pragma region Pitch
void Music::IncreasePitch()
{
	float pitchMax = 4.00f;
	if (pitch >= pitchMax)
	{
		pitch = pitchMax;
	}
	else
	{
		pitch+= PITCH_SPEED*DeltaTime;
	}
	m_music->setPitch(pitch);
}
void Music::DecreasePitch()
{
	float pitchMin = -4.00f;
	if (pitch <= pitchMin)
	{
		pitch = pitchMin;
	}
	else
	{
		pitch-= PITCH_SPEED*DeltaTime;
	}
	m_music->setPitch(pitch);
}
sf::Music* Music::GetMusic()
{
    return	m_music;
}
void Music::ResetPitchVariable()
{
	pitch = 1;
}
float Music::GetPitchVariable()
{
	return pitch;
}
#pragma endregion

#pragma endregion
#pragma region Privates
void Music::SetAllVolume()
{
	m_Soundoptions.load("options.txt");
	m_musicon = m_Soundoptions.get("sound_options","musicon",m_musicon);
	m_musicvol = m_Soundoptions.get("sound_options","musicvolume",m_musicvol) * 10.0f;

	if(!m_musicon || m_musicvol == 0)
	{
		m_music->setVolume(0.0f);
	}
	else
	{
		m_music->setVolume(m_musicvol);
	}
}

void Music::LoadMusic(sf::Music*& musicToLoad, const std::string filename)
{
	musicToLoad = new sf::Music();
	if (musicToLoad->openFromFile(filename))
	{
		std::cout << "Loaded music: " << filename << std::endl;
	}
	else if (!musicToLoad->openFromFile(filename))
	{
		std::cout << "Failed to load music: " << filename << std::endl;
	}
	musicToLoad->setLoop(true);
	SetAllVolume();
}
#pragma endregion