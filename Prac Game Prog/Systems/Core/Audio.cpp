#include "Audio.h"

void Audio::InitAudio()
{
    result = FMOD::System_Create(&audioSystem);
    result = audioSystem->init(32, FMOD_INIT_NORMAL, extraDriverData);
}

void Audio::PlaySound(std::shared_ptr<AudioComponent> au)
{
    auto au2d = std::dynamic_pointer_cast<Audio2DComponent>(au);
    //                                       au->channelGroup, au->isPaused (i think isPause shouldnt be used)
    result = audioSystem->playSound(au2d->sound, 0, false, &channel);
    //TODO: need to set freq and volume
    channel->setVolume(au2d->getVolume());
    //channel->setFrequency(au2d->getFrequency());
    channel->setFrequency(48000);
}

void Audio::UpdateSound()
{
    result = audioSystem->update();
}



