#include "PauseMenuQuitButtonEventScript.h"

void PauseMenuQuitButtonEventScript::RunScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::RunScript(ownerCollider, incomingCollider);
    //std::cout << "Blow up world\n";
    

}

void PauseMenuQuitButtonEventScript::DoEnterCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    if (attackTriggered)
        if (incomingCollider->parent->GetTag() == MOUSE_POINTER)
        {
            std::cout << "Pause Menu Quit Button clicked\n";
            pauseMenuSceneManager->UnloadScene(false);
            pauseMenuSceneManager->LoadScene(MAIN_MENU);
            EventScript::DoEnterCollisionScript(ownerCollider, incomingCollider);
        }
}

void PauseMenuQuitButtonEventScript::DoExitCollisionScript(std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::DoExitCollisionScript(incomingCollider);
    //std::cout << "Stop Blowing up world\n";
}
