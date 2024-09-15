#include "OptionButtonEventScript.h"
#include <iostream>

void OptionButtonEventScript::RunScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::RunScript(ownerCollider, incomingCollider);
    //std::cout << "Blow up world\n";


}

void OptionButtonEventScript::DoEnterCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    if (attackTriggered)
        if (incomingCollider->parent->GetTag() == MOUSE_POINTER)
        {
            std::cout << "Resume Button clicked\n";
            mainMenuSceneManager->UnloadScene(false);
            mainMenuSceneManager->LoadScene(OPTIONS_MENU);
            EventScript::DoEnterCollisionScript(ownerCollider, incomingCollider);
        }
}

void OptionButtonEventScript::DoExitCollisionScript(std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::DoExitCollisionScript(incomingCollider);
    //std::cout << "Stop Blowing up world\n";
}