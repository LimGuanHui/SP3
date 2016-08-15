#include "SP3.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

SP3::SP3()
{
    //sceneSoundEngine = NULL;
}

SP3::~SP3()
{
    /*if (sceneSoundEngine != NULL)
    {
        sceneSoundEngine->drop();
    }*/
}

void SP3::Init()
{
    SceneBase::Init();
    //Calculating aspect ratio

    m_goList.clear();

    m_worldHeight = 100.f;
    m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
    //Physics code here
    m_speed = 1.f;

    Math::InitRNG();

    m_objectCount = 0;

    m_ghost = new GameObject(GameObject::GO_BALL);
    
}




GameObject* SP3::FetchGO()
{
    for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
    {
        GameObject *go = (GameObject *)*it;
        std::vector<GameObject *>::iterator it2 = it;
        if (!go->active)
        {
            go->Init();
            go->active = true;


            ++m_objectCount;
            return go;
        }
    }
    for (unsigned i = 0; i < 10; ++i)
    {
        GameObject *go = new GameObject(GameObject::GO_BALL);
        m_goList.push_back(go);
    }
    GameObject *go = m_goList.back();
    go->active = true;
    ++m_objectCount;
    return go;
}

bool SP3::CheckCollision(GameObject *go1, GameObject *go2, float dt)
{
    switch (go2->type)
    {
    case GameObject::GO_BALL:
    {
                                if (go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_BALL)
                                {
                                    float distanceSquared = ((go1->pos + go1->vel * dt) - (go2->pos - go2->vel * dt)).LengthSquared();
                                    float combinedRadiusSquared = (go1->scale.x + go2->scale.x) * (go1->scale.x + go2->scale.x);
                                    Vector3 relativeVelocity = go1->vel - go2->vel;
                                    Vector3 relativeDisplacement = go2->pos - go1->pos;
                                    return distanceSquared < combinedRadiusSquared && relativeVelocity.Dot(relativeDisplacement) > 0;
                                }
    }

    case GameObject::GO_WALL:
    {
                                Vector3  w0 = go2->pos;
                                Vector3 b1 = go1->pos;
                                Vector3 N = go2->normal;
                                float r = go1->scale.x;
                                float h = go2->scale.x;
                                float l = go2->scale.y;

                                Vector3 NP(-N.y, N.x);

                                Vector3 RV = go1->vel;
                                Vector3 RD = w0 - b1;

                                if (RD.Dot(N) < 0)
                                    N = -N;

                                return abs(RD.Dot(N)) < r + h / 2 && abs(RD.Dot(NP)) < l / 2 && RV.Dot(N) > 0;
    }
    case GameObject::GO_PILLAR:
    {
                                  Vector3 p1 = go1->pos;
                                  Vector3 p2 = go2->pos;
                                  float r1 = go1->scale.x;
                                  float r2 = go2->scale.x;
                                  float combinedRadius = r1 + r2;

                                  Vector3 u = go1->vel;

                                  return (p2 - p1).LengthSquared() < combinedRadius * combinedRadius && (p2 - p1).Dot(u) > 0;
    }


    }
    return false;
}

void SP3::CollisionResponse(GameObject *go1, GameObject *go2)
{
    switch (go2->type)
    {
    case GameObject::GO_BALL:
    {
                                //Exercise 8b: store values in auditing variables
                                m1 = go1->mass;
                                m2 = go2->mass;
                                u1 = go1->vel;
                                u2 = go2->vel;

                                Vector3 u1N, u2N, N;
                                N = (go2->pos - go1->pos).Normalized();

                                u1N = u1.Dot(N) * N;
                                u2N = u2.Dot(N) * N;
                                go1->vel = u1 + (2 * m2) / (m1 + m2) * (u2N - u1N);
                                go2->vel = u2 + (2 * m1) / (m1 + m2) * (u1N - u2N);

                                v1 = go1->vel;
                                v2 = go2->vel;
                                break;
    }
    case GameObject::GO_WALL:
    {
                                Vector3 u = go1->vel;
                                Vector3 N = go2->normal;
                                Vector3 uN = u.Dot(N) * N;
                                go1->vel = u - 2 * uN;
                                break;
    }
    case GameObject::GO_PILLAR:
    {
                                  Vector3 u = go1->vel;
                                  Vector3 N = (go2->pos - go1->pos).Normalized();
                                  go1->vel = u - 2 * u.Dot(N) * N;
                                  break;
    }
    }
}



void SP3::Update(double dt)
{
    SceneBase::Update(dt);

    if (Application::IsKeyPressed('9'))
    {
        m_speed = Math::Max(0.f, m_speed - 0.1f);
    }
    if (Application::IsKeyPressed('0'))
    {
        m_speed += 0.1f;
    }
    //Mouse Section
    static bool bLButtonState = false;
    if (Application::IsMousePressed(0) && !bLButtonState)
    {
        bLButtonState = true;
        std::cout << "LBUTTON DOWN" << std::endl;

    }
    else if (bLButtonState && !Application::IsMousePressed(0))
    {
        bLButtonState = false;
        std::cout << "LBUTTON UP" << std::endl;

    }
    static bool bRButtonState = false;
    if (!bRButtonState && Application::IsMousePressed(1))
    {
        bRButtonState = true;
        std::cout << "RBUTTON DOWN" << std::endl;

       
    }
    else if (bRButtonState && !Application::IsMousePressed(1))
    {
        bRButtonState = false;
        std::cout << "RBUTTON UP" << std::endl;

    }

    //Physics Simulation Section

    /*
    for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
    {
        GameObject *go = (GameObject *)*it;
    }
    */

    for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
    {
        GameObject *go = (GameObject *)*it;
        if (go->active)
        {
            go->pos += go->vel * dt;
            
        }
    }

        


}


void SP3::RenderGO(GameObject *go)
{
    /*
    //rotate code
    modelStack.Rotate(Math::RadianToDegree(atan2(-go->vel.x, go->vel.y)), 0, 0, 1);
    */

    modelStack.PushMatrix();
    Vector3 temp;
    switch (go->type)
    {
    default:
        break;
    }
    modelStack.PopMatrix();

}


void SP3::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    // Projection matrix : Orthographic Projection
    Mtx44 projection;
    projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
    projectionStack.LoadMatrix(projection);

    // Camera matrix
    viewStack.LoadIdentity();
    viewStack.LookAt(
        camera.position.x, camera.position.y, camera.position.z,
        camera.target.x, camera.target.y, camera.target.z,
        camera.up.x, camera.up.y, camera.up.z
        );
    // Model matrix : an identity matrix (model will be at the origin)
    modelStack.LoadIdentity();

    RenderMesh(meshList[GEO_AXES], false);


    for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
    {
        GameObject *go = (GameObject *)*it;
        if (go->active)
        {
            RenderGO(go);
        }
    }

    std::ostringstream ss;
    ss.str(string());
    ss.precision(5);
    ss << "FPS: " << fps;
    RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 3);



}

void SP3::Exit()
{
    SceneBase::Exit();
    //Cleanup GameObjects
    for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
    {
        GameObject *go = (GameObject *)*it;
        go->Init();
    }
    while(m_goList.size() > 0)
    {
    	GameObject *go = m_goList.back();
           delete go;
    	m_goList.pop_back();
    }
    if (m_ghost)
    {
        delete m_ghost;
        m_ghost = NULL;
    }
}