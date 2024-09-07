#include "BoxColliderComponent.h"

#include <algorithm>

#include "../BaseClasses/Entity.h"

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

void BoxColliderComponent::SetBox(RECT box, D3DXVECTOR2 centerPos)
{
    auto t= parent->transform;
    this->box.top = centerPos.y - (box.top+box.bottom)/2;
    this->box.bottom = centerPos.y + (box.top+box.bottom)/2;
    this->box.left = centerPos.x - (box.left+box.right)/2;
    this->box.right = centerPos.x + (box.left+box.right)/2;
}

void BoxColliderComponent::UpdateColliderPos(D3DXVECTOR2 velocity)
{

    this->box.top += velocity.y;
    this->box.bottom += velocity.y;
    this->box.left += velocity.x;
    this->box.right += velocity.x;
    
    if(parent->GetTag() == TagEnum::ENEMY){
        std::cout<<"TOP = "<<this->box.top<<std::endl;
        std::cout<<"BOTTOM = "<<this->box.bottom<<std::endl;
        std::cout<<"LEFT = "<<this->box.left<<std::endl;
        std::cout<<"RIGHT = "<<this->box.right<<std::endl;
        
    }
}
