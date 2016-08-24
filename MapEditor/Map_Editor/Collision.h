#ifndef COLLISION_EXPORTS
#define COLLISION_API __declspec(dllexport) 
#else
#define COLLISION_API __declspec(dllimport) 
#endif

#include "Map_Editor.h"
#include "Character.h"

class COLLISION_API Collision
{
public:
    Collision();
	~Collision();

	CHARACTER::CCharacter* N_Character;
	Map_Editor* Map;
	//Platform* Platform;

    void CheckCollision();
	void CheckCollisionX();
    bool CheckCollisionY();

	void CheckProjectileCollision();

    void Response_X(Platform* go, bool left);
    void Response_Y(Platform* go, bool below);
    void Response(Projectile* go);
    void Init(CHARACTER::CCharacter* C_CHARACTER, Map_Editor* map);
};

COLLISION_API Collision* CreateNewCollisionInstance();