#include "BoxColliderComponent.h"

BoxColliderComponent::BoxColliderComponent() 
    : tag(ColliderTag::Player)
{
    Component(BOX_COLLIDER);
    this->box.top = 0;
    this->box.left = 0;
    this->box.right = 0;
    this->box.bottom = 0;
}

BoxColliderComponent::BoxColliderComponent(RECT box, ColliderTag tag) 
    : tag(tag)
{
    Component(BOX_COLLIDER);
    this->box = box;
}
