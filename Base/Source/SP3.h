#ifndef SP3_H
#define SP3_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"
#include <map>;

#include "Mob.h"
#include "Boss_Battle.h"


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

    GameObject* FetchGO();

    bool CheckCollision(GameObject *go1, GameObject *go2, float dt);
    float CheckCollision2(GameObject *go1, GameObject *go2);
    void CollisionResponse(GameObject *go1, GameObject *go2);

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
		Quit2,
		NUM2
	};

    enum Game_Stage
    {
        Normal,
        Boss,
    };

	enum Select
	{
		First,
		Second,
		NUM3
	};


	Select option;
	int selectArrow = 0;
    GameState gameState;
	string StartOption[NUM];
	string PauseOption[NUM2];
    Game_Stage gameStage;
	int startScreenArrow = 0;
	bool editLevel;
	bool pauseGame;

protected:

    float m_speed;
    float m_worldWidth;
    float m_worldHeight;
    GameObject *m_ghost;


    //Auditing
    float m1, m2;
    Vector3 u1, u2, v1, v2;
    Vector3 initialMomentum, finalMomentum;
    float initialKE, finalKE;

    //Mob
    std::vector<Mob *> mob_list;

    //Boss Battle
    //BossBattle::Boss_Battle *B_battle;
    
    //Menu
    float InputDelayTimer;
};

#endif