#pragma once
#include "AudioComponent.h"

class Audio2DComponent : public AudioComponent 
{
public:
    float pan = 0; // Audio panning (-1 for left, 0 for center, 1 for right)
    
    virtual ~Audio2DComponent() = default;  // Virtual destructor
    Audio2DComponent();
};
