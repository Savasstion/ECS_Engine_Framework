#pragma once
#include <d3dx9.h>
#include <memory>
#include <vector>
#include  "../../Components/Rigidbody2DComponent.h"
#include "../../Components/BoxColliderComponent.h"
#include "../../BaseClasses/Scene.h"

class Physics
{
public:
    D3DXVECTOR2 globalGravity = D3DXVECTOR2(0,1);

    static void DoScenePhysics(std::shared_ptr<Scene> scene);
    static void DoAllCycleOfMotion(std::vector<std::shared_ptr<Component>> rbg2DComponents);    //  for 2D
    static void DoCycleOfMotion(std::shared_ptr<Rigidbody2DComponent> rgb);
    static void HandleCollision(std::vector<std::shared_ptr<Component>> collider);

private:
    static bool CheckCollision(std::shared_ptr<BoxColliderComponent> a, std::shared_ptr<BoxColliderComponent> b);
    static void ResolveCollision(std::shared_ptr<Rigidbody2DComponent> rbA, std::shared_ptr<Rigidbody2DComponent> rbB);
};
