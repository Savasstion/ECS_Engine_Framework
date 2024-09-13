#pragma once
#include <memory>
#include "../../BaseClasses/Sprite.h"
#include "../../Components/TransformComponent.h"
class Entity;


//GAMEPLAY STUFF // TODO : do it someehere else in the future
extern float mainMenuThrust;
extern float mainMenuRotationSpeed;


extern float timeSinceLastSoundMainMenu; // Track time since the last sound was played
extern const float soundIntervalMainMenu; // Time interval between sounds in seconds

extern std::shared_ptr<Entity> audioEntityMainMenu;
extern Sprite spriteInfoMainMenu;
extern Sprite spriteInfo1MainMenu;

//Parallax stuff
extern std::shared_ptr<TransformComponent> background1Transform;
extern std::shared_ptr<TransformComponent> background2Transform;
extern std::shared_ptr<TransformComponent> background3Transform;
extern std::shared_ptr<TransformComponent> background4Transform;
extern std::shared_ptr<TransformComponent> background5Transform;

// For the second set of backgrounds
extern std::shared_ptr<TransformComponent> background1Transform2;
extern std::shared_ptr<TransformComponent> background2Transform2;
extern std::shared_ptr<TransformComponent> background3Transform2;
extern std::shared_ptr<TransformComponent> background4Transform2;
extern std::shared_ptr<TransformComponent> background5Transform2;

extern float parallaxFactor1;
extern float parallaxFactor2;
extern float parallaxFactor3;
extern float parallaxFactor4;
extern float parallaxFactor5;

extern std::shared_ptr<Entity> playerEntity;