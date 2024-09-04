#include "AudioComponent.h"




void AudioComponent::LoadSound(std::string sourcePath, boolean isLooping, boolean isStream)
{
    
    if(isStream)
    {
        auto mode = FMOD_CREATESTREAM;
        result = audioSystem->createSound(sourcePath.c_str(), mode,0,&sound);
    }
    else
    {
        auto mode = FMOD_DEFAULT;
        result = audioSystem->createSound(sourcePath.c_str(), mode,0,&sound);
    }

    if(isLooping)
        result = sound->setMode(FMOD_LOOP_NORMAL);
    else
        result = sound->setMode(FMOD_LOOP_OFF);
}
