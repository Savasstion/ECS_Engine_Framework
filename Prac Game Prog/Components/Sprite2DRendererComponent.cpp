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

void Sprite2DRendererComponent::UpdateSpriteAnimation(int framesToUpdate)
{
    static int frameCounter = 0;

    if (spriteInfo.isAnimated)
    {
        if (spriteInfo.isDirectional)
        {
            std::cout << "Animating Directional" << '\n';

            frameCounter += framesToUpdate;
            int colIndex = frameCounter % (spriteInfo.maxCols + 1);
            int rowIndex = 0;

            if (spriteInfo.currentDirection == spriteInfo.upDirectionValue)
            {
                rowIndex = spriteInfo.upDirectionValue;
                std::cout << "Animating UP" << '\n';
            }
            if (spriteInfo.currentDirection == spriteInfo.leftDirectionValue)
            {
                rowIndex = spriteInfo.leftDirectionValue;
                std::cout << "Animating LEFT" << '\n';
            }
            if (spriteInfo.currentDirection == spriteInfo.rightDirectionValue)
            {
                rowIndex = spriteInfo.rightDirectionValue;
                std::cout << "Animating RIGHT" << '\n';
            }
            if (spriteInfo.currentDirection == spriteInfo.rightDirectionValue)
            {
                rowIndex = spriteInfo.downDirectionValue;
                std::cout << "Animating DOWN" << '\n';
            }

            if (frameCounter % (spriteInfo.maxRows + 1) == 0)
                frameCounter = 0;

            spriteRect.left = colIndex % spriteInfo.totalCols * spriteInfo.spriteWidth;
            spriteRect.top = rowIndex * spriteInfo.spriteHeight;
            spriteRect.right = spriteRect.left + spriteInfo.spriteWidth;
            spriteRect.bottom = spriteRect.top + spriteInfo.spriteHeight;
        }
        else
        {
            std::cout << "Animating Non-Directional" << '\n';
            frameCounter += framesToUpdate;
            int colIndex = frameCounter % spriteInfo.maxFrames % (spriteInfo.maxCols);
            int rowIndex = frameCounter % spriteInfo.maxFrames / (spriteInfo.maxRows);

            if (frameCounter % (spriteInfo.maxRows + 1) == 0)
                frameCounter = 0;

            spriteRect.left = colIndex % spriteInfo.totalCols * spriteInfo.spriteWidth;
            spriteRect.top = rowIndex * spriteInfo.spriteHeight;
            spriteRect.right = spriteRect.left + spriteInfo.spriteWidth;
            spriteRect.bottom = spriteRect.top + spriteInfo.spriteHeight;
        }        
    }
}





