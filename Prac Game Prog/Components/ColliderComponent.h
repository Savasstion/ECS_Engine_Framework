#pragma once
#include <d3dx9math.h>

#include "../BaseClasses/Component.h"


class ColliderComponent : public Component
{
public:
    D3DXVECTOR2 relativePos = D3DXVECTOR2(0,0);
    bool isVisible = false;
    
    virtual ~ColliderComponent() = default;  // Virtual destructor
    virtual void UpdateColliderPos(D3DXVECTOR2 parentPos);


};
