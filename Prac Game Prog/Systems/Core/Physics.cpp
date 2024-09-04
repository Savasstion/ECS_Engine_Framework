#include "Physics.h"

void Physics::DoScenePhysics(std::shared_ptr<Scene> scene)
{
    DoAllCycleOfMotion(scene->componentManager->GetComponents(RIGIDBODY2D));
}

//For Rigidbody 2D
void Physics::DoAllCycleOfMotion(std::vector<std::shared_ptr<Component>> rbg2DComponents)
{
    for (auto c : rbg2DComponents)
    {
        auto rgb = std::dynamic_pointer_cast<Rigidbody2DComponent>(c);
        DoCycleOfMotion(rgb);
    }
}

void Physics::DoCycleOfMotion(std::shared_ptr<Rigidbody2DComponent> rgb)
{
    rgb->velocity += rgb->acceleration;
    rgb->velocity *= (1 - rgb->friction);

    if (rgb->velocity > rgb->maxVelocity)
        rgb->velocity = rgb->maxVelocity;

    if (rgb->parent->transform != nullptr)
        rgb->parent->transform->position += rgb->velocity;
}

void Physics::HandleCollision(std::vector<std::shared_ptr<Component>> colliders)
{
    for (auto c : colliders)
    {
        auto collider = std::dynamic_pointer_cast<BoxColliderComponent>(c);
        DoCycleOfMotion(rgb);
    }
    
}