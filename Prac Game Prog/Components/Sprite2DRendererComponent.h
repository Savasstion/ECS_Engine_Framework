#pragma once
#include "RendererComponent.h"
#include "../BaseClasses/FrameTimer.h"
#include "../BaseClasses/Sprite.h"

#include "../Enums/DirectionEnum.h"

class Sprite2DRendererComponent : public RendererComponent
{
public:
    Sprite spriteInfo;
    //  Sprite rect to cut out specific parts of sprite sheet
    RECT spriteRect;
    D3DXVECTOR2 spriteRenderPos;
    //  int intendedAnimationFPS;
    bool isAnimated;
    
    //default directions
    Direction currentDirection;
    int upDirectionValue = 0;
    int leftDirectionValue = 1;
    int rightDirectionValue = 2;
    int downDirectionValue = 3;

    Sprite2DRendererComponent();
    Sprite2DRendererComponent(Sprite spriteInfo);
    LPDIRECT3DTEXTURE9 GetTexture(){return spriteInfo.texture;}
    void SetTexture(LPDIRECT3DTEXTURE9 newTexture){this->spriteInfo.texture = newTexture;}
    RECT GetRect(){return spriteRect;}
    void SetRect(int top, int bottom, int left, int right);
    void InitSpriteInfo(Sprite spirteInfo);
    Sprite GetSpriteInfo(){return spriteInfo;}
    void SetSpriteInfo(Sprite newSpriteInfo){this->spriteInfo = newSpriteInfo;}
    D3DXVECTOR2 GetSpriteRenderPos();
    D3DXVECTOR2 GetSpriteCenter();
    void UpdateSpriteAnimation(int framesToUpdate);
    void UpdateSpriteAnimationDirection(int framesToUpdate, Direction direction);
};
