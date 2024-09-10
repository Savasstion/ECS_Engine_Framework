#include "Entity.h"
#include "../Components/Sprite2DRendererComponent.h"

Entity::Entity(size_t uid, TagEnum tag)
{
    this->uid = uid;
    this->tag = tag;
}

Entity::Entity(size_t uid, TagEnum tag, std::string name, D3DXVECTOR2 scale, float rotation, D3DXVECTOR2 position)
{
    this->uid = uid;
    this->tag = tag;
    this->name->SetName(name);
    this->transform->scale = scale;
    this->transform->rotation = rotation;
    this->transform->position = position;
}

D3DXMATRIX Entity::GetTransformMatrix()
{
    D3DXMATRIX mat;
    if (transform != NULL)
    {
        auto r = std::dynamic_pointer_cast<Sprite2DRendererComponent>(renderer);
        auto pos = r->GetSpriteRenderPos();
        auto center = r->GetSpriteCenter();
        D3DXMatrixTransformation2D(&mat,&center,transform->rotation,&transform->scale,&center,transform->rotation,&pos);
    }
    // else if(transform != NULL)
    {
       // D3DXMatrixTransformation2D(&mat,NULL,0.0,&transform->scale,NULL,transform->rotation,&transform->position);
    }
        return mat;
}

void Entity::ClearPointers()
{
    transform->Destroy();
    name->Destroy();
    renderer->Destroy();
    for(auto c : colliders)
    {
        c->Destroy();
    }
}


