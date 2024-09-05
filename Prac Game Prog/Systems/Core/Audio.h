#pragma once
#include "../../Systems/Core/Globals.h"
#include "../../Components/Audio2DComponent.h"

class Audio
{
public:
    FMOD_RESULT result;   // For getting error code
    void* extraDriverData; // Ignore


    // Methods for initializing, playing, and updating audio
    void InitAudio();
    void PlaySound(std::shared_ptr<AudioComponent> au);
    void UpdateSound();
};
