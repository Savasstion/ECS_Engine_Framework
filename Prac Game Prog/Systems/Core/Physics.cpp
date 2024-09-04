#include "Physics.h"

void Physics::DoScenePhysics(std::shared_ptr<Scene> scene)
{
    DoAllCycleOfMotion(scene->componentManager->GetComponents(RIGIDBODY2D));
    HandleCollision(scene->componentManager->GetComponents(BOX_COLLIDER));
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

    if (rgb->velocity.x > rgb->maxVelocity.x)
        rgb->velocity.x = rgb->maxVelocity.x;
    if (rgb->velocity.y > rgb->maxVelocity.y)
        rgb->velocity.y = rgb->maxVelocity.y;

    if (rgb->parent->transform != nullptr)
        rgb->parent->transform->position += rgb->velocity;
}

void Physics::HandleCollision(std::vector<std::shared_ptr<Component>> colliders)
{
    //  you may now need to do research on how to check collisions for the whole vector of colliders

    for (auto c : colliders)
    {
        //  this is how you can get a colliderComponent from the vector(arraylist)
        auto collider = std::dynamic_pointer_cast<BoxColliderComponent>(c);
        
    }
    
}

void Physics::HandleCollision(std::vector<std::shared_ptr<Component>> colliders) {
    // Brute force collision detection (improve with spatial partitioning for large numbers of objects)
    for (size_t i = 0; i < colliders.size(); ++i) {
        for (size_t j = i + 1; j < colliders.size(); ++j) {
            auto colliderA = std::dynamic_pointer_cast<BoxColliderComponent>(colliders[i]);
            auto colliderB = std::dynamic_pointer_cast<BoxColliderComponent>(colliders[j]);

            if (CheckCollision(colliderA, colliderB)) {
                auto rbA = std::dynamic_pointer_cast<Rigidbody2DComponent>(colliderA->parent->GetComponent(RIGIDBODY2D));
                auto rbB = std::dynamic_pointer_cast<Rigidbody2DComponent>(colliderB->parent->GetComponent(RIGIDBODY2D));
                ResolveCollision(rbA, rbB);
            }
        }
    }
}

bool Physics::CheckCollision(std::shared_ptr<BoxColliderComponent> a, std::shared_ptr<BoxColliderComponent> b) {
    // Simple AABB (Axis-Aligned Bounding Box) collision detection
    return (a->box.right >= b->box.left &&
        a->box.left <= b->box.right &&
        a->box.bottom >= b->box.top &&
        a->box.top <= b->box.bottom);
}

void Physics::ResolveCollision(std::shared_ptr<Rigidbody2DComponent> rbA, std::shared_ptr<Rigidbody2DComponent> rbB) {
    // Basic collision resolution - inverse the velocity or separate the objects
    if (rbA && rbB) {
        // Elastic collision response (simplified)
        D3DXVECTOR2 normal = rbB->parent->transform->position - rbA->parent->transform->position;
        D3DXVec2Normalize(&normal, &normal);

        float relativeVelocity = D3DXVec2Dot(&(rbB->velocity - rbA->velocity), &normal);
        float e = 1.0f;  // Coefficient of restitution (1 = perfectly elastic, 0 = perfectly inelastic)

        float j = -(1 + e) * relativeVelocity / (1 / rbA->mass + 1 / rbB->mass);

        D3DXVECTOR2 impulse = j * normal;

        rbA->velocity -= impulse / rbA->mass;
        rbB->velocity += impulse / rbB->mass;
    }
}