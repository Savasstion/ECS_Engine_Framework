#pragma once
#include <d3d9.h>
#include <d3dx9math.h>

class Sprite
{
public:
    //  sprite sheet stuff
    LPDIRECT3DTEXTURE9 texture;
    int totalRows, totalCols;
    int sheetWidth, sheetHeight;
    int sheetGap = 0;
    int maxFrames = 1; //total frames
    int fpsFactor = 1;
    bool isAnimated = false;
    bool isDirectional = false;
    bool animating = false;

    int spriteHeight;
    int spriteWidth;

    int currentDirection = 0;

    int upDirectionValue = 0;
    int leftDirectionValue = 1;
    int rightDirectionValue = 2;
    int downDirectionValue = 3;
};
