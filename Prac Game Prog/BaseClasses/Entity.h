#pragma once
#include <d3dx9.h>
#include <memory>
#include <string>
#include <vector>

#include "../Components/AudioComponent.h"
#include "../Components/NameComponent.h"
#include "../Components/RendererComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/ColliderComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Enums/TagEnum.h"


typedef std::vector<std::shared_ptr<ColliderComponent>> Colliders;
typedef std::shared_ptr<TransformComponent> Transform;
typedef std::shared_ptr<NameComponent> Name;
typedef std::shared_ptr<RendererComponent> Renderer;
typedef std::shared_ptr<RigidbodyComponent> Rigidbody;
typedef std::vector<std::shared_ptr<AudioComponent>> Audios;

class Entity
{
    size_t uid = 0;
    TagEnum tag = TagEnum::DEFAULT_TAG;
    bool isActive = true;
public:
    Transform transform;
    Name name;
    Renderer renderer;
    Colliders colliders;
    Rigidbody rigidbody;
    Audios audios;
    
    //  every subclass should have a Start and Update function that calls parent's Start and Update first then its own logic.
    /* TODO : make constructor private so only EntityManager can create Entities    */
    Entity(size_t uid, TagEnum tag);
    Entity(size_t uid, TagEnum tag, std::string name, D3DXVECTOR2 scale, float rotation, D3DXVECTOR2 position);
    D3DXMATRIX GetTransformMatrix();
    TagEnum GetTag(){return tag;}
    bool GetIsActive(){return isActive;}
    void Destroy(){isActive = false;}
    void ClearPointers();
    
};
