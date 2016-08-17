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
#include <irrKlang.h>
using namespace irrklang;

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
	void CharacterAnimation();

    GameObject* FetchGO();

    bool CheckCollision(GameObject *go1, GameObject *go2, float dt);
    float CheckCollision2(GameObject *go1, GameObject *go2);
    void CollisionResponse(GameObject *go1, GameObject *go2);
    void RenderFromList(Boss_Battle* b_battle);

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

	enum StartOption
	{
		Start,
		Edit,
		Load,
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

    enum Game_Stage
    {
        Normal,
        Boss,
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

	// Main Menu
	SelectMain option;
	int selectArrow = 0;

	// Pause Menu
	SelectPause option2;
	int selectArrow2 = 0;

    GameState gameState;
	string StartOption[NUM];
	string PauseOption[NUM2];
    Game_Stage gameStage;
	int startScreenArrow = 0;
	bool editLevel;
	bool pauseGame;

	CCharacter* Character;
	//CMovement* Character;
	ISoundEngine* sceneSoundEngine;

	bool playerDead;

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
    
    //Menu
    float InputDelayTimer;

};

#endif