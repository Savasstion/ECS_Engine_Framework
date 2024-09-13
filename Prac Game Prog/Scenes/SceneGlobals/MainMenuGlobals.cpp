#include "MainMenuGlobals.h"


float mainMenuThrust = 3.5f;
float mainMenuRotationSpeed = .1f;


float timeSinceLastSoundMainMenu = 0.0f; // Track time since the last sound was played
const float soundIntervalMainMenu = 0.1f; // Time interval between sounds in seconds

std::shared_ptr<Entity> audioEntityMainMenu = nullptr;
Sprite spriteInfoMainMenu;
Sprite spriteInfo1MainMenu;


std::shared_ptr<TransformComponent> background1Transform = nullptr;
std::shared_ptr<TransformComponent> background2Transform = nullptr;
std::shared_ptr<TransformComponent> background3Transform = nullptr;
std::shared_ptr<TransformComponent> background4Transform = nullptr;
std::shared_ptr<TransformComponent> background5Transform = nullptr;

// For the second set of backgrounds
std::shared_ptr<TransformComponent> background1Transform2 = nullptr;
std::shared_ptr<TransformComponent> background2Transform2 = nullptr;
std::shared_ptr<TransformComponent> background3Transform2 = nullptr;
std::shared_ptr<TransformComponent> background4Transform2 = nullptr;
std::shared_ptr<TransformComponent> background5Transform2 = nullptr;

float parallaxFactor1 = 1.0f;  // Foreground
float parallaxFactor2 = 0.7f;  // Midground 1
float parallaxFactor3 = 0.4f;  // Midground 2
float parallaxFactor4 = 0.1f;  // Background 1
float parallaxFactor5 = 0.05f; // Background 2
