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
    int maxRows = 0;
    int maxCols = 0;
    
    bool isAnimated = false;

    int spriteHeight;
    int spriteWidth;


};
