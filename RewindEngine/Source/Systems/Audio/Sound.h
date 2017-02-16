#pragma once

#include<irrklang\irrKlang.h>

using namespace irrklang;


class Sound
{
public:

	friend class AudioManager;

	//Constructors and Destructors
	Sound(const char* _path,  const char* _name);
	~Sound();

	//Getters/Setters
	ISoundSource* GetSoundSource();
	ISound* GetSoundObject();
	void SetSoundObject(ISound* soundObject) { m_sound = soundObject; }
	bool IsLooped();


private:
	//name of the sound
	const char* m_name;

	//path of the sound
	const char* m_path;

	//loopSound or not
	bool m_LoopSound;

	//For Effects
	bool m_EnableSoundEffects;

	//to manipulate the sound that is currently being played
	ISound* m_sound;

	//Source of the sound
	ISoundSource* m_source;
};