#pragma once
#include "WindowProcedure.h"

class Graphics
{

public:
    static MSG msg;

    Graphics();
    static bool SpawnWindow();
    static void CleanupWindow();
    static void CleanupD3DDevice();
    static void CleanupDirectXInterfaces();
    static void CleanupLoadedTextures();
    static bool CreateD3DDevice();
    static void DrawInterfaces();
    static int Render();
};