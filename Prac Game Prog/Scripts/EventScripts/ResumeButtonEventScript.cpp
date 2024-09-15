#include "ResumeButtonEventScript.h"

#include <iostream>
#include "../../Systems/Managers/SceneManager.h"

void ResumeButtonEventScript::RunScript(std::shared_ptr<ColliderComponent> ownerCollider,
                                        std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::RunScript(ownerCollider, incomingCollider);
    //std::cout << "Blow up world\n";
    

}

void ResumeButtonEventScript::DoEnterCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    if (attackTriggered)
        if (incomingCollider->parent->GetTag() == MOUSE_POINTER)
        {
            std::cout << "Resume Button clicked\n";
            pauseMenuSceneManager->UnloadScene(false);
            pauseMenuSceneManager->LoadScene(GAME_SCENE);
            EventScript::DoEnterCollisionScript(ownerCollider, incomingCollider);
        }
}

void ResumeButtonEventScript::DoExitCollisionScript(std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::DoExitCollisionScript(incomingCollider);
    //std::cout << "Stop Blowing up world\n";
}