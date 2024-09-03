#pragma once
#include <map>
#include <memory>
#include <vector>
#include "../../Enums/TagEnum.h"
#include "../../BaseClasses/Entity.h"

//  im trading memory for functionality
//  we gonna store a lot more pointers but it may make life easier in the future
typedef std::vector<std::shared_ptr<Entity>> EntityVector;
//  A map so we can get a vector of entities according to their tag
typedef std::map<TagEnum,EntityVector> EntityMap;

class EntityManager
{
    EntityVector entities;
    //  to avoid Iteration Invalidation, store things to add/remove to a waiting list first and do adding and removing when safe to do. It is unsafe to modify a vector during a loop
    EntityVector entitiesToAdd;
    EntityMap entityMap;
    size_t totalEntities = 0;
public:
    void Start();
    void Update();
    std::shared_ptr<Entity> CreateEntity(TagEnum tag);
    std::shared_ptr<Entity> CreateEntity(TagEnum tag, std::string name, D3DXVECTOR2 scale, float rotation, D3DXVECTOR2 position);
    EntityVector& GetEntities();
    EntityVector& GetEntities(TagEnum tag);
    std::shared_ptr<Entity> GetEntity(TagEnum tag);
    void DestroyAllEntities();


};
