#pragma once
#include <memory>
#include "../../BaseClasses/Sprite.h"
#include "../../Components/Polygon2DColliderComponent.h"


class Entity;

//GAMEPLAY STUFF // TODO : do it someehere else in the future
extern float Thrust;
extern float gameSceneRotationSpeed;

extern int currentTrashCount;

extern float timeSinceLastSoundGameScene; // Track time since the last sound was played
extern const float soundIntervalGameScene; // Time interval between sounds in seconds

extern std::shared_ptr<Entity> audioEntityGameScene;
extern Sprite spriteInfogGameScene;
extern Sprite spriteInfo1GameScene;

extern std::shared_ptr<Entity> playerEntity;
extern std::shared_ptr<Entity> goalEntity;

extern std::shared_ptr<Polygon2DColliderComponent> octagonCollider;
extern std::shared_ptr<Polygon2DColliderComponent> attackColliderL;
extern std::shared_ptr<Polygon2DColliderComponent> attackColliderR;
extern std::shared_ptr<Polygon2DColliderComponent> truckCollider;
extern std::shared_ptr<Polygon2DColliderComponent> truckGoalCollider;
