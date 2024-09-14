#pragma once
#include <memory>

class ColliderComponent;

class EventScript
{
private:
    bool isDoneOnce = false;
public:
    //override and make child classes
    virtual void RunScript(std::shared_ptr<ColliderComponent> ownerCollider, std::shared_ptr<ColliderComponent> incomingCollider);
    virtual void DoEnterCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider, std::shared_ptr<ColliderComponent> incomingCollider);
    virtual void DoExitCollisionScript(std::shared_ptr<ColliderComponent> incomingCollider);

    //In child class header,
    //  void RunScript(std::shared_ptr<ColliderComponent> ownerCollider, std::shared_ptr<ColliderComponent> incomingCollider) override;
    //  void DoEnterCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider, std::shared_ptr<ColliderComponent> incomingCollider)override;
    //  void DoExitCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider, std::shared_ptr<ColliderComponent> incomingCollider)override;


    //In child class cpp,
    //void ChildClass::RunScript(std::shared_ptr<ColliderComponent> ownerCollider, std::shared_ptr<ColliderComponent> incomingCollider)
    //{
    //  EventScript::RunScript(ownerCollider, incomingCollider);
    //
    //  insert stuff here // every update or every time when still in collision
    //}
    //
    //void ChildClass::DoEnterCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider, std::shared_ptr<ColliderComponent> incomingCollider)
    //{
    //  EventScript::DoEnterCollisionScript(ownerCollider, incomingCollider);
    //  insert stuff here // do once when first enter collision
    //
    //}
    //
    //void ChildClass::DoExitCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider, std::shared_ptr<ColliderComponent> incomingCollider)
    //{
    //  EventScript::DoExitCollisionScript(ownerCollider, incomingCollider);
    //  insert stuff here // do when no more collision
    //
    //}
    
};
