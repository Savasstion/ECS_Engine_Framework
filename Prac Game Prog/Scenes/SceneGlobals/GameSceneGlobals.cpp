#include "GameSceneGlobals.h"


float gameSceneThrust = 3.5f;
float gameSceneRotationSpeed = .1f;


float timeSinceLastSoundGameScene = 0.0f; // Track time since the last sound was played
const float soundIntervalGameScene = 0.1f; // Time interval between sounds in seconds

std::shared_ptr<Entity> audioEntityGameScene = nullptr;
Sprite spriteInfogameScene;
Sprite spriteInfo1gameScene;

std::shared_ptr<Entity> playerEntity;
std::shared_ptr<Entity> goalEntity;

std::shared_ptr<Polygon2DColliderComponent> octagonCollider;
std::shared_ptr<Polygon2DColliderComponent> attackColliderL;
std::shared_ptr<Polygon2DColliderComponent> attackColliderR;
std::shared_ptr<Polygon2DColliderComponent> truckCollider;
std::shared_ptr<Polygon2DColliderComponent> truckGoalCollider;