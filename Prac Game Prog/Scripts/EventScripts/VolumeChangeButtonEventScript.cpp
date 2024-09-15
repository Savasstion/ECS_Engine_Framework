#include "VolumeChangeButtonEventScript.h"
#include "../../Scenes/SceneGlobals/OptionSceneGlobals.h"


void VolumeChangeButtonEventScript::RunScript(std::shared_ptr<ColliderComponent> ownerCollider,
                                              std::shared_ptr<ColliderComponent> incomingCollider)
{
    if (attackTriggered)
        if (incomingCollider->parent->GetTag() == MOUSE_POINTER)
        {
            std::cout << "Volume Change Button clicked\n";
            if (isIncrementVolume)
            {
                volumeModifier += .1f;
                if (volumeModifier > 1.0f)
                    volumeModifier = 1.0f;
            }
            else
            {
                volumeModifier -= .1f;
                if (volumeModifier < 0.0f)
                    volumeModifier = 0.0f;
            }

            EventScript::RunScript(ownerCollider, incomingCollider);
        }
    //std::cout << "Blow up world\n";
    

}

void VolumeChangeButtonEventScript::DoEnterCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::DoEnterCollisionScript(ownerCollider, incomingCollider);
}

void VolumeChangeButtonEventScript::DoExitCollisionScript(std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::DoExitCollisionScript(incomingCollider);
    //std::cout << "Stop Blowing up world\n";
}
