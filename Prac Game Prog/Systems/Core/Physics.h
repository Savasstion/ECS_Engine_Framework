#pragma once
#include <d3dx9.h>
#include <memory>
#include <vector>
#include  "../../Components/Rigidbody2DComponent.h"
#include "../../BaseClasses/Scene.h"

class Physics
{
public:
    D3DXVECTOR2 globalGravity = D3DXVECTOR2(0,1);

    static void DoScenePhysics(std::shared_ptr<Scene> scene);
    static void DoAllCycleOfMotion(std::vector<std::shared_ptr<Component>> rbg2DComponents);    //  for 2D
};
