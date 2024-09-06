#include "EntityManager.h"

void EntityManager::Start()
{
    DoAllEntityStartups();
}

void EntityManager::UpdateEntityList()
{
    //  entities in to_be_added list is added to main lists
    for(auto e : entitiesToAdd)
    {
        entities.push_back(e);
        entityMap[e->GetTag()].push_back(e);
    }

    for(auto e : entitiesToAdd)
    {
        e->Start();
    }
    entitiesToAdd.clear();

    //  check all entities if not active, remove from main lists
    for(auto e : entities)
    {
        if(!e->GetIsActive())
        {
            //  clear e's pointers
            e->ClearPointers();
            //  move e to the end of vector and change the end of vector to leave out e
            entities.erase(std::remove(entities.begin(), entities.end(), e), entities.end());
            entityMap[e->GetTag()].erase(std::remove(entityMap[e->GetTag()].begin(), entityMap[e->GetTag()].end(), e), entityMap[e->GetTag()].end());
        }
    }

        
}

void EntityManager::DoAllEntityStartups()
{
    //  Do all entities' Start function
    for(auto e : entities)
    {
        e->Start();
    }
}

void EntityManager::DoAllEntityUpdates()
{
    //  do all entity updates
    for(auto e : entities)
    {
        e->Update();
    }
}

std::shared_ptr<Entity> EntityManager::CreateEntity(TagEnum tag)
{
    //  code doesnt handle some map-related edge cases
    auto e = std::make_shared<Entity>(totalEntities++, tag);
    entitiesToAdd.push_back(e);
    return e;
}

std::shared_ptr<Entity> EntityManager::CreateEntity(TagEnum tag, std::string name, D3DXVECTOR2 scale, float rotation, D3DXVECTOR2 position)
{
    //  code doesnt handle some map-related edge cases
    auto e = std::make_shared<Entity>(totalEntities++, tag, name, scale, rotation,position);
    entitiesToAdd.push_back(e);
    return e;
}

EntityVector& EntityManager::GetEntities()
{
    return entities;
}

EntityVector& EntityManager::GetEntities(TagEnum tag)
{
    return entityMap[tag];
}

std::shared_ptr<Entity> EntityManager::GetEntity(TagEnum tag)
{
    return entityMap[tag][0];
}

std::shared_ptr<Entity> EntityManager::GetEntity(TagEnum tag, int index)
{
    return entityMap[tag][index];
}

void EntityManager::DestroyAllEntities()
{
    for(auto e : entities)
    {
        e->Destroy();
    }
}


