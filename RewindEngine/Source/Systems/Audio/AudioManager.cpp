#include <precompiled.h>
#include "AudioManager.h"
#include "Sound.h"
#include <iostream>

using namespace std;


std::string AudioManager::GetName() const
{
	return "AudioManager";
}
#pragma region "Constructors/Destructors"
AudioManager::AudioManager()
{
	//Create a sound device context
}

AudioManager::~AudioManager()
{
	//Unload the sound engine
	Unload();
	//Deleting the sound engine
	m_soundEngine->drop();
}
#pragma region endregion

#pragma region "Public Methods"
bool AudioManager::Initialize(void)
{
	m_soundEngine = createIrrKlangDevice();

	//Checking if the sound engine is initialized correctly
	if (!m_soundEngine)
	{
		std::cout << "Error starting the sound engine" << std::endl;
		return false;
	}
	else
	{
		return true;
	}
}

void AudioManager::Update(float dt) 
{
	//Do update
}

void AudioManager::ReceiveMessage(Message* msg)
{

}
void AudioManager::LoadSound(char* path, char* name)
{

	//Pushes back the sound into the list of sound objects
	AddSound(new Sound(path, name));

}

void AudioManager::Play(const char* name)
{
	//Loop through the sound list and find the sound to be played
	std::list<Sound* >::const_iterator iter;

	for (iter = m_SoundList.begin(); iter != m_SoundList.end(); iter++)
	{
		if ((*iter)->m_name == name)
		{
			(*iter)->m_sound = m_soundEngine->play2D((*iter)->m_path, (*iter)->m_LoopSound, false, false, ESM_AUTO_DETECT, (*iter)->m_EnableSoundEffects);
			
		}
		else
		{
			//report that the sound name is not present
		}
	}



}

void AudioManager::AddSound(Sound* sound)
{
	//Push the sound object into the list 
	m_SoundList.push_back(sound);
}

void AudioManager::PauseSound(const char* nameOfSound, bool isPaused)
{
	std::list<Sound* >::const_iterator iter;

	for (iter = m_SoundList.begin(); iter != m_SoundList.end(); iter++)
	{
		if ((*iter)->m_name == nameOfSound)
		{
			if ((*iter)->GetSoundObject())
			{
				(*iter)->GetSoundObject()->setIsPaused(isPaused);
			}
			
		}
		else
		{
			//report that the sound name is not present
		}
	}
	
}

void AudioManager::StopAllSound()
{
	m_soundEngine->setAllSoundsPaused();
}

void AudioManager::SetSoundVolume(const char* nameOfSound, const float& _volume)
{
	std::list<Sound* >::const_iterator iter;

	for (iter = m_SoundList.begin(); iter != m_SoundList.end(); iter++)
	{
		if ((*iter)->m_name == nameOfSound)
		{
			if ((*iter)->GetSoundObject())
			{
				(*iter)->GetSoundObject()->setVolume(_volume);
			}

		}
		else
		{
			//report that the sound name is not present
		}
	}

}

void AudioManager::Unload(void)
{
	//Clear the sound oject List
	m_SoundList.clear();

	//delete the sound engine
	m_soundEngine->drop();

}

#pragma endregion