#include "AudioComponent.h"




void AudioComponent::LoadSound(std::string sourcePath, boolean isLooping, boolean isStream)
{
    
    if(isStream)
        result = audioSystem->createStream(sourcePath.c_str(), FMOD_DEFAULT,0,&sound);
    else
        result = audioSystem->createSound(sourcePath.c_str(), FMOD_DEFAULT,0,&sound);
    

    if(isLooping)
        result = sound->setMode(FMOD_LOOP_NORMAL);
    else
        result = sound->setMode(FMOD_LOOP_OFF);
}
