#pragma once
#include <memory>
#include "../../BaseClasses/Sprite.h"
#include "../../Systems/Core/Audio.h"


class Entity;


//GAMEPLAY STUFF // TODO : do it someehere else in the future
extern float thrust;
extern float rotationSpeed;


extern float timeSinceLastSound; // Track time since the last sound was played
extern const float soundInterval; // Time interval between sounds in seconds

extern std::shared_ptr<Entity> audioEntity;
extern Sprite spriteInfo;
extern Sprite spriteInfo1;

extern Audio audioManager;

extern std::shared_ptr<Entity> mousePointerEntity;


