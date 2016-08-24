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

class COLLISION_API HOTSPOT
{
public:
    HOTSPOT();
    ~HOTSPOT();
    void Init(Vector3 scale, int numHotspots_height, int numHotspots_width, float offset);
    void Run();

    void Set_detectionheight(float detectionheight);
    void Set_detectionwidth(float detectionwidth);
    void Set_collisionheight(float collisionheight);
    void Set_collisionwidth(float collisionwidth);
    void Set_hotspotwidth(float hotspotwidth);
    void Set_hotspotheight(float hotspotheight);

private:
    float detection_height, detection_width;
    float collision_height, collision_width;
    int hotspot_width, hotspot_height;
    std::vector<Vector3> hotspot_List;
};