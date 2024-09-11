#include "Audio.h"

void Audio::InitAudio()
{
    result = FMOD::System_Create(&audioSystem);
    result = audioSystem->init(32, FMOD_INIT_NORMAL, extraDriverData);
}

void Audio::PlayAudio(std::shared_ptr<AudioComponent> au, float spriteX, float screenWidth)
{
    auto au2d = std::dynamic_pointer_cast<Audio2DComponent>(au);
    //                                       au->channelGroup, au->isPaused (i think isPause shouldnt be used)
    result = audioSystem->playSound(au2d->sound, 0, false, &channel);
    //TODO: need to set freq and volume
    channel->setVolume(au2d->GetVolume());
    channel->setFrequency(48000);
    
    float normalizedPan = (spriteX / screenWidth) * 2.0f - 1.0f;
    if (normalizedPan < -1.0f) normalizedPan = -1.0f;
    if (normalizedPan > 1.0f) normalizedPan = 1.0f;

    channel->setPan(normalizedPan);
}

void Audio::UpdateSound()
{
    result = audioSystem->update();
}



