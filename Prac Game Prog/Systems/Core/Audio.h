#pragma once
#include "../../Components/AudioComponent.h"
#include "../../Systems/Core/Globals.h"
class Audio
{
public:
    FMOD_RESULT result;	//	for getting error code
    void* extraDriverData = 0;	//	ignore
    
    void InitAudio();
    void PlaySound(std::shared_ptr<AudioComponent> au);
    void UpdateSound();
};
