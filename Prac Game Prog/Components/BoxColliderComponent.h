#pragma once
#include "ColliderComponent.h"
#include "d3d9.h"

class BoxColliderComponent : public ColliderComponent
{
public:
    RECT box;
    BoxColliderComponent();
    BoxColliderComponent(RECT box);
    
};
