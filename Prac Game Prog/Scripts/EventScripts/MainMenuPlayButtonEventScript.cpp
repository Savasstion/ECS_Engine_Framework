#include "MainMenuPlayButtonEventScript.h"
#include "../../Scenes/SceneGlobals/MainMenuGlobals.h"
void MainMenuPlayButtonEventScript::RunScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::RunScript(ownerCollider, incomingCollider);
    //std::cout << "Blow up world\n";
    

}

void MainMenuPlayButtonEventScript::DoEnterCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    if (attackTriggered)
        if (incomingCollider->parent->GetTag() == MOUSE_POINTER)
        {
            std::cout << "Play Button clicked\n";
            mainMenuSceneManager->UnloadScene(false);
            mainMenuSceneManager->LoadScene(GAME_SCENE);
            EventScript::DoEnterCollisionScript(ownerCollider, incomingCollider);
        }
}

void MainMenuPlayButtonEventScript::DoExitCollisionScript(std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::DoExitCollisionScript(incomingCollider);
    //std::cout << "Stop Blowing up world\n";
}
