#include <precompiled.h>
#include "Engine\Engine.h"
#include "Sound.h"
#include "AudioManager.h"

//global pointer


#pragma region "Constructors/Destructors"
Sound::Sound(const char* _path, const char* _name):m_path(_path),m_name(_name), m_LoopSound(true), m_EnableSoundEffects(false)
{
	//Set the sound Source by getting the audioManager
	AudioManager * audioManager = dynamic_cast<AudioManager*>(Engine::GetEngineSingleton().GetSystem("AudioManager"));
	m_source = audioManager->GetSoundEngine()->addSoundSourceFromFile(m_path);

}

Sound::~Sound()
{
	//When sound is done playing we can delete the resources allocated
	m_source->drop();
}
#pragma endregion

#pragma region "Public Methods"

ISoundSource* Sound::GetSoundSource()
{
	return m_source;
}

ISound* Sound::GetSoundObject()
{
	return m_sound;
}

bool Sound::IsLooped()
{
	return m_LoopSound;
}

#pragma endregion
