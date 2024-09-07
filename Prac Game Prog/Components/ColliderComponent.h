#pragma once
#include <d3dx9math.h>

#include "../BaseClasses/Component.h"


class ColliderComponent : public Component
{
public:
    virtual ~ColliderComponent() = default;  // Virtual destructor
    virtual void UpdateColliderPos(D3DXVECTOR2 velocity);
};
