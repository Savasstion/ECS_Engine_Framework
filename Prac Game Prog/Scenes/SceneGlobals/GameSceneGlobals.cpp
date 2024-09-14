#include "GameSceneGlobals.h"


float gameSceneThrust = 3.5f;
float gameSceneRotationSpeed = .1f;


float timeSinceLastSoundgameScene = 0.0f; // Track time since the last sound was played
const float soundIntervalgameScene = 0.1f; // Time interval between sounds in seconds

std::shared_ptr<Entity> audioEntitygameScene = nullptr;
Sprite spriteInfogameScene;
Sprite spriteInfo1gameScene;

std::shared_ptr<Polygon2DColliderComponent> octagonCollider;
std::shared_ptr<Polygon2DColliderComponent> attackColliderL;
std::shared_ptr<Polygon2DColliderComponent> attackColliderR;