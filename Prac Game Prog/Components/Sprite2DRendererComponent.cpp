#include "Sprite2DRendererComponent.h"

#include "../BaseClasses/Entity.h"


Sprite2DRendererComponent::Sprite2DRendererComponent()
{
    Component(SPRITE2D_RENDERER);
}

Sprite2DRendererComponent::Sprite2DRendererComponent(Sprite spriteInfo)
{
    Component(SPRITE2D_RENDERER);
    InitSpriteInfo(spriteInfo);
}


void Sprite2DRendererComponent::SetRect(int top, int bottom, int left, int right)
{
    spriteRect.top = top;
    spriteRect.bottom = bottom;
    spriteRect.left = left;
    spriteRect.right = right;
}

void Sprite2DRendererComponent::InitSpriteInfo(Sprite spriteInfo)
{
    this->spriteInfo = spriteInfo;
    //  Set initial spriteRect
    spriteRect.top = 0;
    spriteRect.bottom = spriteInfo.sheetHeight;
    spriteRect.left = 0;
    spriteRect.right = spriteInfo.spriteWidth;


}

D3DXVECTOR2 Sprite2DRendererComponent::GetSpriteRenderPos()
{
    int x = parent->transform->position.x - spriteInfo.spriteWidth/2;
    int y =parent->transform->position.y - spriteInfo.spriteHeight/2;
    return D3DXVECTOR2(x,y);
}

D3DXVECTOR2 Sprite2DRendererComponent::GetSpriteCenter()
{
    int x = spriteInfo.spriteWidth/2;
    int y = spriteInfo.spriteHeight/2;
    
    return D3DXVECTOR2(x,y);
}





