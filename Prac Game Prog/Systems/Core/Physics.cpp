#include "Physics.h"
#undef min
#undef max 

const float Physics::globalGravityConstant = 1.0f;

void Physics::DoScenePhysics(std::shared_ptr<Scene> scene, int framesToUpdate)
{
    for(int i =0;i<framesToUpdate;i++)
    {
        DoAllCycleOfMotion(scene);
        HandleAllCollision(scene);
    }
}


void Physics::DoAllCycleOfMotion(std::shared_ptr<Scene> scene)
{
    //  do Rigidbody2D cycle of motion
    auto rgb2Ds = scene->componentManager->GetComponents(RIGIDBODY2D);
    for (auto c : rgb2Ds)
    {
        if(c != nullptr)
        {
            auto rgb = std::dynamic_pointer_cast<Rigidbody2DComponent>(c);
            DoCycleOfMotion2D(rgb);
        }
    }
}

void Physics::DoCycleOfMotion2D(std::shared_ptr<Rigidbody2DComponent> rgb)
{
    if(!rgb->isStatic)
    {
        if (rgb->mass != 0.0f) {
            rgb->acceleration = rgb->forceApplied / rgb->mass;
        } else {
            rgb->acceleration = D3DXVECTOR2(0, 0); // Prevent division by zero
        }
    
        D3DXVECTOR2 frictionForce = CalculateFrictionForce(rgb->velocity, rgb->friction, rgb->mass);

        rgb->acceleration += frictionForce / rgb->mass;

        rgb->velocity += rgb->acceleration;
    
        //  caps velocity to max velocity
        if (D3DXVec2Length(&rgb->velocity) > D3DXVec2Length(&rgb->maxVelocity))
        {
            D3DXVec2Normalize(&rgb->velocity,&rgb->velocity);
            rgb->velocity *= D3DXVec2Length(&rgb->maxVelocity);
        }

        if (rgb->parent != nullptr)
            rgb->parent->transform->position += rgb->velocity;

        rgb->forceApplied = D3DXVECTOR2(0,0);   //resets force being applied on entity
    }
}

void Physics::HandleAllCollision(std::shared_ptr<Scene> scene)
{
    auto components = scene->componentManager->GetComponents(POLYGON2D_COLLIDER);
    
    for(size_t i = 0; i < components.size(); i++)
    {
        auto polygon2dCollider = std::dynamic_pointer_cast<Polygon2DColliderComponent>(components[i]);
        if(polygon2dCollider->parent != nullptr)
        {
            // Update prevSet to be the current state
            polygon2dCollider->prevTriggeredColliders = polygon2dCollider->currentTriggeredColliders;
            // Clear currentSet for the next update cycle
            polygon2dCollider->currentTriggeredColliders.clear();
        }
    }
    
    //  Check for Polygon2D collision
    for(size_t i = 0; i < components.size(); i++)
    {
            auto polygon2dColliderA = std::dynamic_pointer_cast<Polygon2DColliderComponent>(components[i]);
            if(polygon2dColliderA->parent != nullptr)
            {
                for(size_t j = i+1; j < components.size(); j++)
                {
                    auto polygon2dColliderB = std::dynamic_pointer_cast<Polygon2DColliderComponent>(components[j]);  
                    if(polygon2dColliderB->parent != nullptr)
                    {
                        D3DXVECTOR2 normal= D3DXVECTOR2(0,0);
                        float depth = std::numeric_limits<float>::max();
                        auto isCollided = CheckIfPolygons2DIntersect(polygon2dColliderA->GetColliderVerticesInWorld(), polygon2dColliderB->GetColliderVerticesInWorld(), &normal, &depth);

                        //  do collision routine
                        if(isCollided)
                        {
                            polygon2dColliderB->currentTriggeredColliders.insert(polygon2dColliderA);
                            polygon2dColliderA->currentTriggeredColliders.insert(polygon2dColliderB);
                    
                            //std::cout<<"COLLISION_DETECTED!"<<'\n';
                    
                            //  Do polygon2dColliderA collision event
                            if(polygon2dColliderA->collsionEventScript != nullptr)
                            {
                                // polygon2dColliderA->collisionEvent->ownerCollider = polygon2dColliderA;
                                // polygon2dColliderA->collisionEvent->incomingCollider = polygon2dColliderB;
                                // auto listenerIDA = polygon2dColliderA->AddCollisionListener();
                                // polygon2dColliderA->collisionEvent->TriggerEvent();
                                // polygon2dColliderA->collisionEvent->RemoveListener(listenerIDA);
                                polygon2dColliderA->collsionEventScript->RunScript(polygon2dColliderA, polygon2dColliderB);
                            }

                            //  Do polygon2dColliderB collision event
                            if(polygon2dColliderB->collsionEventScript != nullptr)
                            {
                                // polygon2dColliderB->collisionEvent->ownerCollider = polygon2dColliderB;
                                // polygon2dColliderB->collisionEvent->incomingCollider = polygon2dColliderA;
                                // auto listenerIDB = polygon2dColliderB->AddCollisionListener();
                                // polygon2dColliderB->collisionEvent->TriggerEvent();
                                // polygon2dColliderB->collisionEvent->RemoveListener(listenerIDB);
                                polygon2dColliderB->collsionEventScript->RunScript(polygon2dColliderB, polygon2dColliderA);
                            }

                            //  Move colliders apart from each other to resolve physical intersection
                            if(!polygon2dColliderA->isEventTrigger && !polygon2dColliderB->isEventTrigger)
                            {
                                if(polygon2dColliderA->parent->rigidbody != nullptr && polygon2dColliderB->parent->rigidbody != nullptr)
                                {
                                    auto rgb2dA = std::dynamic_pointer_cast<Rigidbody2DComponent>(polygon2dColliderA->parent->rigidbody);
                                    auto rgb2dB = std::dynamic_pointer_cast<Rigidbody2DComponent>(polygon2dColliderB->parent->rigidbody);

                                    if(!rgb2dA->isStatic)
                                        polygon2dColliderA->parent->transform->position += (-normal * depth/2.0f);
                                    if(!rgb2dB->isStatic)
                                        polygon2dColliderB->parent->transform->position += (normal * depth/2.0f);

                                    //  Add forces for realistic physics response

                                    ResolveCollision(rgb2dA, rgb2dB, normal, depth);
                                }
                            }
                        }
                    }
                }
            }
    }
    
    for(size_t i = 0; i < components.size(); i++)
    {
        auto collider = std::dynamic_pointer_cast<Polygon2DColliderComponent>(components[i]);
        if(collider->parent != nullptr)
            collider->DoAllExitCollisions();
    }
     
}

void Physics::ProjectVerticesOntoAxis(std::vector<D3DXVECTOR2> vertices, D3DXVECTOR2 axis, float* minValue, float* maxValue)
{
    
    *minValue = std::numeric_limits<float>::max();
    *maxValue = std::numeric_limits<float>::min();

    for(int i = 0; i < vertices.size(); i++)
    {
    D3DXVECTOR2 v = vertices[i];
        float projection = D3DXVec2Dot(&v,&axis);

        if(projection < *minValue) {*minValue = projection;}
        if(projection > *maxValue) {*maxValue = projection;}
    }
    
}


D3DXVECTOR2 Physics::FindArithmeticMean(std::vector<D3DXVECTOR2> vertices)
{
    float sumX = 0.0f;
    float sumY = 0.0f;
    
    for(size_t i = 0; i < vertices.size(); i++)
    {
        D3DXVECTOR2 v = vertices[i];
        sumX += v.x;
        sumY += v.y;
    }

    return D3DXVECTOR2(sumX / (float)vertices.size(), sumY / (float)vertices.size());
}

void Physics::ResolveCollision(std::shared_ptr<Rigidbody2DComponent> rbA, std::shared_ptr<Rigidbody2DComponent> rbB,
    D3DXVECTOR2 normal, float depth)
{
    //  Referenced using Chris Hecker's Physics Part 3 : Collision Response
    
    auto relativeVelocity = rbB->velocity - rbA->velocity;
    
    float restitution;
    //get the smaller restitution between the two bodies
    if(rbA->restitution < rbB->restitution)
        restitution = rbA->restitution;
    else
        restitution = rbB->restitution;
    
    float magnitude = - (1 + restitution) * D3DXVec2Dot(&relativeVelocity, &normal);
    magnitude /= (1.0f / rbA->mass) + (1.0f / rbB->mass);


    //rbA->velocity -= magnitude / rbA->mass * normal;
    //rbA->velocity += magnitude / rbB->mass * normal;
    rbA->ApplyForce(-magnitude / rbA->mass * normal);
    rbB->ApplyForce(magnitude / rbB->mass * normal);

}

bool Physics::CheckIfPolygons2DIntersect(std::vector<D3DXVECTOR2> verticesA, std::vector<D3DXVECTOR2> verticesB, D3DXVECTOR2* normal, float* depth)
{   //  SAT (Separating Axis Theorem)
    //  Taken reference from Two-Bit Coding on YouTube
    //  Note : make sure only pass it convex polygons, TODO: take account for non-convex polygons
    
    for(size_t i = 0; i < verticesA.size(); i++)
    {
        D3DXVECTOR2 vA = verticesA[i];
        D3DXVECTOR2 vB = verticesA[(i + 1) % verticesA.size()]; //  circular loop of vertices

        //  get direction vector from vA to vB
        D3DXVECTOR2 edge = vB- vA;
        
        //  get axis
        //  swap x and y and get the sin component of the new x (put in new x for clockwise normals, put in new y for counter-clockwise)
        D3DXVECTOR2 axis = D3DXVECTOR2(-edge.y, edge.x);

        //  we project the vertices onto the axis for a number line to check mins and maxes
        float minA, maxA, minB, maxB;
        ProjectVerticesOntoAxis(verticesA, axis, &minA, &maxA);
        ProjectVerticesOntoAxis(verticesB, axis, &minB, &maxB);

        if(minA >= maxB || minB >= maxA)
        {   //  if true, means there is a gap between the two polygons
            return false;
        }

        //  Resolve Collision
        //  get smallest depth of collision
        float axisDepth;
        auto v1 = maxA - minB;
        auto v2 = maxB - minA;
        //  get the smaller of the two
        if(v1 < v2)
            axisDepth = v1;
        else
            axisDepth = v2;

        if(axisDepth < *depth)
        {
            *depth = axisDepth;
            *normal = axis;
        }
        
            
    }

    for(size_t i = 0; i < verticesB.size(); i++)
    {
        D3DXVECTOR2 vA = verticesB[i];
        D3DXVECTOR2 vB = verticesB[(i + 1) % verticesB.size()]; //  circular loop of vertices

        //  get direction vector from vA to vB
        D3DXVECTOR2 edge = vB- vA;
        
        //  get axis
        //  swap x and y and get the sin component of the new x (put in new x for clockwise normals, put in new y for counter-clockwise)
        D3DXVECTOR2 axis = D3DXVECTOR2(-edge.y, edge.x);
        D3DXVec2Normalize(&axis, &axis);

        //  we project the vertices onto the axis for a number line to check mins and maxes
        float minA, maxA, minB, maxB;
        ProjectVerticesOntoAxis(verticesA, axis, &minA, &maxA);
        ProjectVerticesOntoAxis(verticesB, axis, &minB, &maxB);

        if(minA >= maxB || minB >= maxA)
        {   //  if true, means there is a gap between the two polygons
            return false;
        }
        
        //  Resolve Collision
        //  get smallest depth of collision
        float axisDepth;
        auto v1 = maxA - minB;
        auto v2 = maxB - minA;
        //  get the smaller of the two
        if(v1 < v2)
            axisDepth = v1;
        else
            axisDepth = v2;

        if(axisDepth < *depth)
        {
            *depth = axisDepth;
            *normal = axis;
        }
    }

    *depth /= D3DXVec2Length(normal);

    //  find center of polygon collider
    auto centerA = FindArithmeticMean(verticesA);
    auto centerB = FindArithmeticMean(verticesB);

    auto direction = centerB - centerA;

    if(D3DXVec2Dot(&direction, normal) < 0.0f)
    {
        *normal *= -1;
    }
    
    return true;
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
