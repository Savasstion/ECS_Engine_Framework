#include "Physics.h"

float Physics::globalGravityConstant = 4.0f;

void Physics::DoScenePhysics(std::shared_ptr<Scene> scene, int framesToUpdate)
{
    for(int i = 0; i < framesToUpdate;i++)
    {
            DoAllCycleOfMotion(scene->componentManager->GetComponents(RIGIDBODY2D));
            HandleAllCollision(scene->componentManager->GetComponents(BOX_COLLIDER));
    }
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

    if (rgb->mass != 0.0f) {
        rgb->acceleration = rgb->forceApplied / rgb->mass;
    } else {
        rgb->acceleration = D3DXVECTOR2(0, 0); // Prevent division by zero
    }

    //rgb->acceleration +=  rgb->forceApplied /  rgb->mass;

    //  caps acceleration to max acceleration;
    if (rgb->acceleration.x > rgb->maxAcceleration.x)
        rgb->acceleration.x = rgb->maxAcceleration.x;
    if (rgb->acceleration.y > rgb->maxAcceleration.y)
        rgb->acceleration.y = rgb->maxAcceleration.y;
    
    //  caps velocity to max velocity
    if (rgb->velocity.x > rgb->maxVelocity.x)
        rgb->velocity.x = rgb->maxVelocity.x;
    if (rgb->velocity.y > rgb->maxVelocity.y)
        rgb->velocity.y = rgb->maxVelocity.y;
    

     D3DXVECTOR2 frictionForce = CalculateFrictionForce(rgb->velocity, rgb->friction, rgb->mass);

    rgb->acceleration += frictionForce / rgb->mass;

    rgb->velocity += rgb->acceleration;

    if (rgb->parent->transform != nullptr)
        rgb->parent->transform->position += rgb->velocity;

    rgb->forceApplied = D3DXVECTOR2(0,0);   //resets force being applied on entity
    //rgb->acceleration = D3DXVECTOR2(0,0);
    //rgb->velocity = D3DXVECTOR2(0,0); 
}

// void Physics::HandleCollision(std::vector<std::shared_ptr<Component>> colliders)
// {
//     //  you may now need to do research on how to check collisions for the whole vector of colliders
//
//     for (auto c : colliders)
//     {
//         //  this is how you can get a colliderComponent from the vector(arraylist)
//         auto collider = std::dynamic_pointer_cast<BoxColliderComponent>(c);
//         
//     }
//     
// }

void Physics::HandleAllCollision(std::vector<std::shared_ptr<Component>> colliders) {
    for (size_t i = 0; i < colliders.size(); ++i) {
        for (size_t j = i + 1; j < colliders.size(); ++j) {
            auto colliderA = std::dynamic_pointer_cast<BoxColliderComponent>(colliders[i]);
            auto colliderB = std::dynamic_pointer_cast<BoxColliderComponent>(colliders[j]);

            if (CheckCollision(colliderA, colliderB)) {
                if (ShouldCollide(colliderA, colliderB)) {
                    auto rbA = std::dynamic_pointer_cast<Rigidbody2DComponent>(colliderA->parent->rigidbody);
                    auto rbB = std::dynamic_pointer_cast<Rigidbody2DComponent>(colliderB->parent->rigidbody);
                    ResolveCollision(rbA, rbB);
                }
            }
        }
    }
}

bool Physics::CheckCollision(std::shared_ptr<BoxColliderComponent> a, std::shared_ptr<BoxColliderComponent> b) {
    return (a->box.right >= b->box.left &&
        a->box.left <= b->box.right &&
        a->box.bottom >= b->box.top &&
        a->box.top <= b->box.bottom);
}


bool Physics::ShouldCollide(std::shared_ptr<BoxColliderComponent> a, std::shared_ptr<BoxColliderComponent> b) {
    if ((a->tag == ColliderTag::Player && b->tag == ColliderTag::Enemy) ||
        (a->tag == ColliderTag::Enemy && b->tag == ColliderTag::Player) ||

        (a->tag == ColliderTag::Player && b->tag == ColliderTag::PowerUp) ||
        (a->tag == ColliderTag::PowerUp && b->tag == ColliderTag::Player) ||
        
        (a->tag == ColliderTag::Player && b->tag == ColliderTag::Player)
        )
    {
        return true;
    }
    return false;
}

void Physics::ResolveCollision(std::shared_ptr<Rigidbody2DComponent> rbA, std::shared_ptr<Rigidbody2DComponent> rbB) {
    if (rbA && rbB) {
        // Calculate the collision normal
        D3DXVECTOR2 normal = rbB->parent->transform->position - rbA->parent->transform->position;
        D3DXVec2Normalize(&normal, &normal);

        D3DXVECTOR2 relativeVelocity = rbB->velocity - rbA->velocity;

        // Check if either of the bodies is bouncy
        bool isBouncyCollision = rbA->bouncy || rbB->bouncy;
        float e = isBouncyCollision ? 1.0f : 0.0f;  // Coefficient of restitution (1 for elastic, 0 for inelastic)

        float relativeVelocityDotNormal = D3DXVec2Dot(&relativeVelocity, &normal);
        if (relativeVelocityDotNormal > 0) {
            return;
        }

        float j = -(1 + e) * relativeVelocityDotNormal / (1 / rbA->mass + 1 / rbB->mass);

        D3DXVECTOR2 impulse = j * normal;

        float timeStep = 1.0f;
        D3DXVECTOR2 force = impulse / timeStep;

        rbA->ApplyForce(-force);
        rbB->ApplyForce(force);

        //INELASTIC
        if (!isBouncyCollision) {
            rbA->velocity *= 0.5f;
            rbB->velocity *= 0.5f;
        }
    }
}

D3DXVECTOR2 Physics::CalculateFrictionForce(D3DXVECTOR2 velocity, float friction, float mass)
{
    // Calculate the friction force opposing the motion
        if (D3DXVec2Length(&velocity) == 0.0f)
        {
            return D3DXVECTOR2(0, 0);  // No friction if there's no movement
        }

        // Calculate the normal force (mass * gravity)
        float normalForce = mass * globalGravityConstant;

        // Calculate kinetic friction magnitude
        float frictionMagnitude = friction * normalForce;

        D3DXVECTOR2 normalizedVelocity;
        D3DXVec2Normalize(&normalizedVelocity, &velocity);
    
        // Friction force is opposite the direction of velocity
        D3DXVECTOR2 frictionForce = -frictionMagnitude * normalizedVelocity;

        // Prevent friction from reversing velocity (optional stability check)
        if (D3DXVec2Length(&frictionForce) > D3DXVec2Length(&velocity) * mass) {
            frictionForce = -velocity * mass;
        }

        return frictionForce;
}
