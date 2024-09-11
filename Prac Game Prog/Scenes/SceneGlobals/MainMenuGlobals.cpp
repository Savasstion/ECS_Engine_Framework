#include "MainMenuGlobals.h"


float thrust = 3.5f;
float rotationSpeed = .1f;


float timeSinceLastSound = 0.0f; // Track time since the last sound was played
const float soundInterval = 0.1f; // Time interval between sounds in seconds

std::shared_ptr<Entity> audioEntity = nullptr;
Sprite spriteInfo;
Sprite spriteInfo1;

Audio audioManager;