#pragma once
#include "Systems\Core\ISystem.h"
#include <list>
#include<irrklang\irrKlang.h>

using namespace irrklang;

//forward declaration of the sound class
class Sound;


class AudioManager : public ISystem
{
public:
	//constructors/destructors
	AudioManager();
	~AudioManager();

	//Create a Soundengine object and it to the list of Sounds
	
	virtual bool Initialize(void);

	//virtual update
	virtual void Update(float dt);

	void LoadSound(char* path, char* name);

	void AddSound(Sound* sound);
	
	//Play the required Sound
	void Play(const char* name);

	//Pauses or Unpauses the sound
	void PauseSound(const char* nameOfSound, bool isPaused);

	//Stops all currently playing sound
	void StopAllSound();

	//Set a volume of the sound
	void SetSoundVolume(const char* nameOfSound , const float& _volume);

	//Get the reference to the sound engine
	ISoundEngine* GetSoundEngine()const { return m_soundEngine; }

	//delete the sounds list and delete the sound engine
	virtual void Unload(void) ;

	virtual void ReceiveMessage(Message* msg) override;

	std::string GetName() const;

	//Will store the list of sounds to be played in the game
	std::list<Sound* > m_SoundList;

private:
	

	//Pointer to the sound engine
	ISoundEngine* m_soundEngine;

	
};