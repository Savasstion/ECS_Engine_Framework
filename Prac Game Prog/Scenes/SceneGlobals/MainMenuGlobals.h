#pragma once
#include <memory>
#include "../../BaseClasses/Sprite.h"
#include "../../Systems/Core/Audio.h"

class Entity;


//GAMEPLAY STUFF // TODO : do it someehere else in the future
extern float mainMenuThrust;
extern float mainMenuRotationSpeed;


extern float timeSinceLastSoundMainMenu; // Track time since the last sound was played
extern const float soundIntervalMainMenu; // Time interval between sounds in seconds

extern std::shared_ptr<Entity> audioEntityMainMenu;
extern Sprite spriteInfoMainMenu;
extern Sprite spriteInfo1MainMenu;

