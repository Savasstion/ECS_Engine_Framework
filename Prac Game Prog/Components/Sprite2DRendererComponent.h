#pragma once
#include "RendererComponent.h"
#include "../BaseClasses/FrameTimer.h"
#include "../BaseClasses/Sprite.h"

class Sprite2DRendererComponent : public RendererComponent
{
public:
    Sprite spriteInfo;
    //  Sprite rect to cut out specific parts of sprite sheet
    RECT spriteRect;
    D3DXVECTOR2 spriteRenderPos;

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
