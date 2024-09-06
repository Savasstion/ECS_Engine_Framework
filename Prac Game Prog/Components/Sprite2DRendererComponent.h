#pragma once
#include "RendererComponent.h"
#include "../BaseClasses/FrameTimer.h"
#include "../BaseClasses/Sprite.h"

class Sprite2DRendererComponent : public RendererComponent
{
private :
    //Entity parent;
    //  used to choose sprite sheet row
    enum Direction{DOWN, UP, RIGHT, LEFT};
public:
    Sprite spriteInfo;
    //  Sprite rect to cut out specific parts of sprite sheet
    RECT spriteRect;
    //  default = 0 so if an animated sprite doesn't change directions, it will not offset to a separate row
    int currentDirection = 0;
    D3DXVECTOR2 spriteRenderPos;
    //  int intendedAnimationFPS;
    bool isAnimated;
    

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
};
