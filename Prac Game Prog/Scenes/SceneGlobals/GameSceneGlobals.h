#pragma once
#include <memory>
#include "../../BaseClasses/Sprite.h"



class Entity;

//GAMEPLAY STUFF // TODO : do it someehere else in the future
extern float Thrust;
extern float gameSceneRotationSpeed;


extern float timeSinceLastSoundgameScene; // Track time since the last sound was played
extern const float soundIntervalgameScene; // Time interval between sounds in seconds

extern std::shared_ptr<Entity> audioEntitygameScene;
extern Sprite spriteInfogameScene;
extern Sprite spriteInfo1gameScene;
