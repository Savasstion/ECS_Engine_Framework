#pragma once
#include <d3dx9.h>
#include <memory>
#include <vector>
#include  "../../Components/Rigidbody2DComponent.h"
#include "../../Components/BoxColliderComponent.h"
#include "../../BaseClasses/Scene.h"
#include <limits>
#include <set>
#include <algorithm>
#include "../../Components/Polygon2DColliderComponent.h"


class Physics
{
public:
    static const float globalGravityConstant;

    
    static void DoScenePhysics(std::shared_ptr<Scene> scene, int framesToUpdate);
    
    //  Motion
    static D3DXVECTOR2 CalculateFrictionForce(D3DXVECTOR2 velocity, float friction, float mass);
    //  Collision
    static bool CheckIfPolygons2DIntersect(std::vector<D3DXVECTOR2> verticesA, std::vector<D3DXVECTOR2> verticesB, D3DXVECTOR2* normal, float* depth);

private:
    //  Motion
    static void DoAllCycleOfMotion(std::shared_ptr<Scene> scene);    
    static void DoCycleOfMotion2D(std::shared_ptr<Rigidbody2DComponent> rgb);
    //  Collision
    static void HandleAllCollision(std::shared_ptr<Scene> scene);
    static void ProjectVerticesOntoAxis(std::vector<D3DXVECTOR2> vertices, D3DXVECTOR2 axis, float* minValue, float* maxValue);
    static D3DXVECTOR2 FindArithmeticMean(std::vector<D3DXVECTOR2> vertices);
    //static bool CheckCollision(std::shared_ptr<BoxColliderComponent> a, std::shared_ptr<BoxColliderComponent> b);
    //static bool ShouldCollide(std::shared_ptr<BoxColliderComponent> a, std::shared_ptr<BoxColliderComponent> b);
    static void ResolveCollision(std::shared_ptr<Rigidbody2DComponent> rbA, std::shared_ptr<Rigidbody2DComponent> rbB, D3DXVECTOR2 normal, float depth);

};
