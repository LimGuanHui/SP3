#ifndef SP3_H
#define SP3_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"
#include <map>;
#include "Panel.h"


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
    std::vector<Panel *> PanelList;
    //Physics

    enum GameState
    {
        Menu,
        Game,
        Transition,
        End,
    };

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

};

#endif