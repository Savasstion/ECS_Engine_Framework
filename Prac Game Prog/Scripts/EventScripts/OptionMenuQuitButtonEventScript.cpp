#include "OptionMenuQuitButtonEventScript.h"

void OptionMenuQuitButtonEventScript::RunScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::RunScript(ownerCollider, incomingCollider);
    //std::cout << "Blow up world\n";
    

}

void OptionMenuQuitButtonEventScript::DoEnterCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    if (attackTriggered)
        if (incomingCollider->parent->GetTag() == MOUSE_POINTER)
        {
            std::cout << "Option Menu Quit Button clicked\n";
            optionSceneManager->UnloadScene(false);
            optionSceneManager->LoadScene(PAUSE_MENU);
            EventScript::DoEnterCollisionScript(ownerCollider, incomingCollider);
        }
}

void OptionMenuQuitButtonEventScript::DoExitCollisionScript(std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::DoExitCollisionScript(incomingCollider);
    //std::cout << "Stop Blowing up world\n";
}
