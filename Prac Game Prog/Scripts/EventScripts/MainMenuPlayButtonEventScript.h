#pragma once
#include "../EventScript.h"
#include "../../Systems/Managers/SceneManager.h"

class MainMenuPlayButtonEventScript : public EventScript
{
public:
    void RunScript(std::shared_ptr<ColliderComponent> ownerCollider, std::shared_ptr<ColliderComponent> incomingCollider)override;
    void DoEnterCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider, std::shared_ptr<ColliderComponent> incomingCollider)override;
    void DoExitCollisionScript(std::shared_ptr<ColliderComponent> incomingCollider)override;

};
