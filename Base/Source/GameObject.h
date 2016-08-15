#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"
#include <string>

using std::string;

struct GameObject
{
	enum GAMEOBJECT_TYPE
	{
		GO_NONE = 0,
		GO_BALL,
		GO_WALL,
		GO_MOVING_WALL,
        GO_MOVING_WALL_PILLAR,
		GO_BREAKABLE_WALL,
		GO_BREAKABLE_WALL_PILLAR,
        GO_FORCE_WALL,
		GO_CUBE,
		GO_PILLAR,
		GO_PLAYER,
		GO_PLAYER_SHOT,
		GO_GOAL,
		GO_GOAL_PILLAR,
		GO_CURVED_WALL,
        GO_STRAIGHT_WALL,
        GO_HOLE,
        GO_BASIC_ENEMY,
        GO_NORMAL_ENEMY,
        GO_NORMAL_ENEMY_BULLET,
        GO_HOMING_ENEMY_BULLET,
        GO_BOSS_ENEMY,
        GO_SHIELD,
		/*GO_ASTEROID,
        GO_BABYASTEROID,
		GO_SHIP,
        GO_ENEMYSHIP,
		GO_BULLET,
		GO_MISSILE,
        GO_ENEMYMISSILE,
		GO_POWERUP,
        GO_ULTIMATE,
        GO_PULSE,*/
		GO_TOTAL, //must be last
	};
	GAMEOBJECT_TYPE type;
	Vector3 pos;
	Vector3 vel;
	Vector3 scale;
    Vector3 normal;
	bool active;
	float mass;
    string name;

    GameObject* connect;

	//for moving walls
	bool up;
	float moveSpeed;
	float moveTime;
	float moveDebouncetimer;

    //enemy
    int hp;
    float interpolation;
    float fireTimer;

    //deflector
    int DeflectorNo;

	GameObject(GAMEOBJECT_TYPE typeValue = GO_BALL);
    void Init();
    void exit();
	~GameObject();
};

#endif