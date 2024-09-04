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
        rgb->DoCycleOfMotion();
    }
}
