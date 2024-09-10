#include "Polygon2DColliderComponent.h"

#include "../BaseClasses/Entity.h"


Polygon2DColliderComponent::Polygon2DColliderComponent()
{
    Component(POLYGON2D_COLLIDER);
    this->colliderTag = ColliderTag::DEFAULT_COLLIDER;
}

std::vector<D3DXVECTOR2> Polygon2DColliderComponent::GetColliderVerticesInWorld()
{
    //  apply entity's transform onto collider as well
    D3DXMATRIX matRotation;
    D3DXMATRIX matScaling;
    D3DXMATRIX matTransform;

    D3DXMatrixRotationZ(&matRotation, parent->transform->rotation);
    D3DXMatrixScaling(&matScaling, parent->transform->scale.x, parent->transform->scale.y, 1.0f); // Scaling in the x and y axes
    D3DXMatrixMultiply(&matTransform, &matScaling, &matRotation);

    // Transform each vertex
    std::vector<D3DXVECTOR2> transformedVertices;
    for (auto& vertex : vertices)
    {
        // Promote the 2D vertex to 4D for transformation
        D3DXVECTOR4 transformedVertex;
        D3DXVec2Transform(&transformedVertex, &vertex, &matTransform);

        // Store the transformed 2D vertex back, dropping the z and w components
        transformedVertices.emplace_back(transformedVertex.x, transformedVertex.y);
    }

    std::vector<D3DXVECTOR2> result;
    result.clear();

    //  move collider vertices to position relative to parent entity
    for(auto v : transformedVertices)
    {
        auto vertex = v + parent->transform->position + relativePos;
        result.emplace_back(vertex);
    }
    
    return result;
}
