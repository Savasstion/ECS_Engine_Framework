#pragma once
#include "../EventScript.h"
#include  "../../Systems/Managers/InputManager.h"
#include "../../BaseClasses/Entity.h"
#include "../../Components/ColliderComponent.h"
#include "../../Components/Rigidbody2DComponent.h"
#include "../../Scenes/SceneGlobals/OptionSceneGlobals.h"
#include "../../Systems/Managers/SceneManager.h"

class OptionButtonEventScript : public EventScript
{
public:
    void RunScript(std::shared_ptr<ColliderComponent> ownerCollider, std::shared_ptr<ColliderComponent> incomingCollider)override;
    void DoEnterCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider, std::shared_ptr<ColliderComponent> incomingCollider)override;
    void DoExitCollisionScript(std::shared_ptr<ColliderComponent> incomingCollider)override;

};