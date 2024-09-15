#include "FullscreenButtonEventScript.h"

#include "../../Scenes/SceneGlobals/OptionSceneGlobals.h"

void FullscreenButtonEventScript::RunScript(std::shared_ptr<ColliderComponent> ownerCollider,
                                            std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::RunScript(ownerCollider, incomingCollider);
    //std::cout << "Blow up world\n";
    

}

void FullscreenButtonEventScript::DoEnterCollisionScript(std::shared_ptr<ColliderComponent> ownerCollider,
    std::shared_ptr<ColliderComponent> incomingCollider)
{
    if (attackTriggered)
        if (incomingCollider->parent->GetTag() == MOUSE_POINTER)
        {
            //  FULLSCREEN routine
            std::cout << "Fullscreen Button clicked\n";
            //destory sprite brush since it holds d3ddevice
            spriteBrush->Release();
            spriteBrush = nullptr;
            lineInterface->Release();
            lineInterface = nullptr;
            fontInterface->Release();
            fontInterface = nullptr;
            //change the Presentation Params for the D3DDevice and then reset it to take effect
            if (d3dPP.Windowed) {
                //if windowed, set to fullscreen
                d3dPP.Windowed = false;
            }
            else
            {
                //else, set to windowed
                d3dPP.Windowed = true;
            }
            HRESULT hr = d3dDevice->Reset(&d3dPP);
            if (FAILED(hr))
            {
                std::cout << "Error : " << DXGetErrorString(hr) << "\nDescription : " << DXGetErrorDescription(hr) << '\n';
            }

            
            EventScript::DoEnterCollisionScript(ownerCollider, incomingCollider);
        }
}

void FullscreenButtonEventScript::DoExitCollisionScript(std::shared_ptr<ColliderComponent> incomingCollider)
{
    EventScript::DoExitCollisionScript(incomingCollider);
    //std::cout << "Stop Blowing up world\n";
}
