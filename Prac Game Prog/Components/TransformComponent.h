#pragma once
#include <d3dx9.h>

#include "../BaseClasses/Component.h"

class TransformComponent : public Component
{
public:
    D3DXVECTOR2 position = D3DXVECTOR2(0,0);
    D3DXVECTOR2 scale = D3DXVECTOR2(1,1);
    float rotation = 0.0f;

    TransformComponent();
    
};
