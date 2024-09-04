#include "Audio.h"

void Audio::InitAudio()
{
    result = FMOD::System_Create(&audioSystem);
    result = audioSystem->init(32, FMOD_INIT_NORMAL, extraDriverData);
}

void Audio::PlaySound(std::shared_ptr<AudioComponent> au)
{
    //                                       au->channelGroup, au->isPaused (i think isPause shouldnt be used)
    result = audioSystem->playSound(au->sound, 0, false, &channel);
    //TODO: need to set freq and volume
}

void Audio::UpdateSound()
{
    result = audioSystem->update();
}



