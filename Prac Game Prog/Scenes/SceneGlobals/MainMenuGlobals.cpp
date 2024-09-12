#include "MainMenuGlobals.h"


float mainMenuThrust = 3.5f;
float mainMenuRotationSpeed = .1f;


float timeSinceLastSoundMainMenu = 0.0f; // Track time since the last sound was played
const float soundIntervalMainMenu = 0.1f; // Time interval between sounds in seconds

std::shared_ptr<Entity> audioEntityMainMenu = nullptr;
Sprite spriteInfoMainMenu;
Sprite spriteInfo1MainMenu;
