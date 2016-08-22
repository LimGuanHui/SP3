#ifndef SP3_H
#define SP3_H

//#include "GameObject.h"
#include <vector>
#include "SceneBase.h"
#include <map>;

#include "GameObject.h"
#include "Mob.h"
#include "Movement.h"
using namespace MOVEMENT;
#include "Boss_Battle.h"

#include "Character.h"
using namespace CHARACTER;
#include "Movement.h"
using namespace MOVEMENT;
#include "Skills.h"
using namespace SKILLS;
#include "Attribute.h"
using namespace ATTRIBUTE;

#include "AI.h"
using namespace AI;

#include <irrKlang.h>
using namespace irrklang;

#include "Map_Editor.h"

#include "Buttons.h"

class SP3 : public SceneBase
{
public:
    SP3();
    ~SP3();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();

    void RenderGO(GameObject *go);
	void RenderProjectile(PROJECTILE::Projectile* projectile);
	void CharacterAnimation();

    GameObject* FetchGO();

    bool CheckCollision(GameObject *go1, GameObject *go2, float dt);
    float CheckCollision2(GameObject *go1, GameObject *go2);
    void CollisionResponse(GameObject *go1, GameObject *go2);
    void RenderFromList(Boss_Battle* b_battle, Map_Editor* map_editor);
    void RenderText();
	void RenderCharacter();
	void RenderProjectile();
	void RenderUI();
    Vector3 CheckMousepos();
    void RenderEditorSelector();
    void loadmap();
    int m_objectCount = 0;
    std::vector<GameObject *> m_goList; //m_goList[0][1];
    
    //Physics

    enum GameState
    {
        EditMode,
        Menu,
        Pause,
        Game,
        Transition,
        End,
    };

    enum Game_Stage
    {
        Normal,
        Boss,
    };

	enum StartOption
	{
		Start,
		Load,
		Edit,
		Quit,
		NUM
	};

	enum PauseOption
	{
		Resume,
		Menu2,
		Quit2,
		NUM2
	};

	enum DeathOption
	{
		Restart,
		Menu3,
		Quit3,
		NUM6
	};

	enum WinOption
	{
		Menu4,
		Quit4,
		NUM8
	};

    

	enum SelectMain
	{
		First,
		Second,
		Third,
		Fourth,
		NUM3
	};

	enum SelectPause
	{
		First2,
		Second2,
		Third2,
		NUM4,
	};

	enum SelectDeath
	{
		First3,
		Second3,
		Third3,
		NUM5,
	};

	enum SelectWin
	{
		First4,
		Second4,
		NUM7
	};

	// Main Menu
	SelectMain option;
	int selectArrow = 0;

	// Pause Menu
	SelectPause option2;
	int selectArrow2 = 0;

	// Death Menu
	SelectDeath option3;
	int selectArrow3 = 0;

	// Victory Menu
	SelectWin option4;
	int selectArrow4 = 0;

    GameState gameState;
    Game_Stage gameStage;
	int startScreenArrow = 0;

	CCharacter* Character;
	ArtInt* AI;
	//CMovement* Character;
	ISoundEngine* sceneSoundEngine;

	bool playerDead;

	Buttons Play;

protected:

    float m_speed;
    float m_worldWidth;
    float m_worldHeight;
    GameObject* m_ghost;


    //Auditing
    float m1, m2;
    Vector3 u1, u2, v1, v2;
    Vector3 initialMomentum, finalMomentum;
    float initialKE, finalKE;

    //Mob
    //std::vector<Mob *> mob_list;

    //Boss Battle
    Boss_Battle* test_B_battle;

    //Map Editor
    Map_Editor* mapEditor;
    
    //Menu
    float InputDelayTimer;

	float firingDebounce;
	static const int fireRate = 10;
	bool Fire;
	bool chargeFire;
	float chargeTime;
};

#endif