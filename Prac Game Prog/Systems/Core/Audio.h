#pragma once
#include "../../Components/AudioComponent.h"
#include "../../Systems/Core/Globals.h"

class Audio
{
public:
    FMOD_RESULT result;   // For getting error code
    void* extraDriverData; // Ignore

    // Methods for initializing, playing, and updating audio
    void InitAudio();
    void PlaySound(std::shared_ptr<AudioComponent> au);
    void UpdateSound();
private:
    FMOD::System* audioSystem; // FMOD audio system instance
    FMOD::Channel* channel;   // FMOD channel instance for playback
};
