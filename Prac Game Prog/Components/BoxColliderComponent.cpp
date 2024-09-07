#include "BoxColliderComponent.h"

BoxColliderComponent::BoxColliderComponent() 
{
    Component(BOX_COLLIDER);
    this->box.top = 0;
    this->box.left = 0;
    this->box.right = 0;
    this->box.bottom = 0;
    this->tag = ColliderTag::Enemy;
}

BoxColliderComponent::BoxColliderComponent(RECT box, ColliderTag tag) 
{
    Component(BOX_COLLIDER);
    this->box = box;
    this->tag = tag;
}
