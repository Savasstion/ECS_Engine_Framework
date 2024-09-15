#include "MainMenuQuitButtonEventScript.h"

#include "../../Scenes/SceneGlobals/MainMenuGlobals.h"

void MainMenuQuitButtonEventScript::RunScript(std::shared_ptr<ColliderComponent> ownerCollider,
                                              std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::RunScript(ownerCollider, incomingCollider);
    //std::cout << "Blow up world\n";
    

}

void MainMenuQuitButtonEventScript::DoEnterCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    if (attackTriggered)
        if (incomingCollider->parent->GetTag() == MOUSE_POINTER)
        {
            std::cout << "Resume Button clicked\n";
            PostQuitMessage(0);
            EventScript::DoEnterCollisionScript(ownerCollider, incomingCollider);
        }
}

void MainMenuQuitButtonEventScript::DoExitCollisionScript(std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::DoExitCollisionScript(incomingCollider);
    //std::cout << "Stop Blowing up world\n";
}
