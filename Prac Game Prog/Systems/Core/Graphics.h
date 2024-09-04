#pragma once
#include <memory>
#include <vector>
#include "../../BaseClasses/Entity.h"
#include "../../BaseClasses/Scene.h"
#include "WindowProcedure.h"
#include "../../Components/Sprite2DRendererComponent.h"

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
    static void DrawInterfacesOfScene(std::shared_ptr<Scene> currentScene);
    static int RenderScene(std::shared_ptr<Scene> currentScene);
    static void DrawAll2DSprites(std::vector<std::shared_ptr<Component>> sprite2DRendererComponents);
};
