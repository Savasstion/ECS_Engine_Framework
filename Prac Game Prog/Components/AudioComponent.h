#pragma once
#include <vector>

#include "../Systems/Core/Globals.h"
#include "../BaseClasses/Component.h"


class AudioComponent : public Component
{
public:
	FMOD::Sound* sound; //sound files
	FMOD_RESULT result;	//	for getting error code

	virtual ~AudioComponent() = default; // Virtual destructor
	void LoadSound(std::string sourcePath, boolean isLooping,boolean isStream);
	float GetVolume(){return volume;}
	float GetFrequency(){return frequency;}
	void setVolume(float volume){this->volume = volume;}
	void setFrequency(long frequency){this->frequency = frequency;}
	
private :
	float volume = 0.5; // sound volume from 0-1
	long frequency = 48000; // Audio frequency ( playback speed and pitch )
	//boolean isPaused = false; // Audio paused or not
	
	
    
};
