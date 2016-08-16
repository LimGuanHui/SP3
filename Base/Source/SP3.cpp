#include "SP3.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>
#define InputDelay 0.1f

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


    Mob* testMob = CreateMob(5.0f);
    testMob->Init();

	quitGame = false;
	editLevel = false;
	pauseGame = false;


    gameState = Menu;
    gameStage = Normal;
	
	StartOption[Start] = "Start Game";
	StartOption[Quit] = "Quit Game";
	StartOption[Edit] = "Edit Level";
	StartOption[Load] = "Load Level";
	PauseOption[Resume] = " Resume";
	PauseOption[Quit2] = "Quit Game";

	//B_battle = new BossBattle::Boss_Battle();
	//B_battle->Init();

    //Menu
    InputDelayTimer = 0;

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
    }
}



void SP3::Update(double dt)
{
    SceneBase::Update(dt);

    if (InputDelayTimer > 0)
        InputDelayTimer -= dt;

	if (gameState == Menu)
	{
        if (Application::IsKeyPressed(VK_DOWN) && InputDelayTimer <= 0)
		{
            InputDelayTimer = InputDelay;
			if (startScreenArrow != (NUM - 1))
				startScreenArrow++;
			else
				startScreenArrow = 0;
		}
        if (Application::IsKeyPressed(VK_UP) && InputDelayTimer <= 0)
		{
            InputDelayTimer = InputDelay;
			if (startScreenArrow != 0)
				startScreenArrow--;
			else
				startScreenArrow = NUM - 1;
		}
		if (Application::IsKeyPressed(VK_RETURN))
		{
			switch (startScreenArrow)
			{
			case(Start) :
				gameState = Game;
				break;
			case(Edit) :
				gameState = EditMode;
				break;
			case(Load) :
				
				break;
			case(Quit) :
				quitGame = true;
				break;
			}
		}
	}

	if (gameState == Game)
	{
		if (Application::IsKeyPressed('P'))
		{
			pauseGame = true;
		}
		if (pauseGame == true)
		{
			if (Application::IsKeyPressed(VK_DOWN) && InputDelayTimer <= 0)
			{
				InputDelayTimer = InputDelay;
				if (startScreenArrow != (NUM2 - 1))
					startScreenArrow++;
				else
					startScreenArrow = 0;
			}
			if (Application::IsKeyPressed(VK_UP) && InputDelayTimer <= 0)
			{
				InputDelayTimer = InputDelay;
				if (startScreenArrow != 0)
					startScreenArrow--;
				else
					startScreenArrow = NUM2 - 1;
			}
			if (Application::IsKeyPressed(VK_RETURN))
			{
				switch (startScreenArrow)
				{
				case(Resume) :
					gameState = Game;
					pauseGame = false;
					break;
				case(Quit2) :
					quitGame = true;
					break;
				}
			}
		}
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

    
    switch (gameState)
    {
    case SP3::EditMode:
    {

    }
        break;
    case SP3::Menu:
    {

    }
        break;
    case SP3::Pause:
    {

    }
        break;
    case SP3::Game:
    {
        switch (gameStage)
        {
        case SP3::Normal:
        {

        }
            break;
        case SP3::Boss:
        {

        }
            break;
        default:
            break;
        }
    }
        break;
    case SP3::Transition:
    {
        //Transition here


        gameState = Game;
    }
        break;
    case SP3::End:
    {

    }
        break;
    default:
        break;
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
    RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 0);

	if (gameState == Menu)
	{
		modelStack.PushMatrix();
		modelStack.Translate(65.f, 50.f, 0.f);
		modelStack.Scale(115, 90, 0);
		RenderMesh(meshList[GEO_UI], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Welcome", Color(0, 0, 1), 4, 25, 50);
		RenderTextOnScreen(meshList[GEO_TEXT], "To", Color(0, 0, 1), 4, 35, 45);
		RenderTextOnScreen(meshList[GEO_TEXT], "Suk Malcolm Deek", Color(0, 0, 1), 4, 8, 40);
		RenderTextOnScreen(meshList[GEO_TEXT], "^", Color(1, 0, 0), 4, 38.5, 20);
		RenderTextOnScreen(meshList[GEO_TEXT], "v", Color(1, 0, 0), 4, 38.5, 10);
		RenderTextOnScreen(meshList[GEO_TEXT], StartOption[startScreenArrow], Color(1, 0, 0), 4, 22.5, 15);
		modelStack.PopMatrix();
	}

	if (pauseGame == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(65.f, 50.f, 0.f);
		modelStack.Scale(115, 90, 0);
		RenderMesh(meshList[GEO_UI], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Game Paused", Color(1, 0, 0), 4, 19, 30);
		RenderTextOnScreen(meshList[GEO_TEXT], "^", Color(1, 0, 0), 4, 38.5, 20);
		RenderTextOnScreen(meshList[GEO_TEXT], "v", Color(1, 0, 0), 4, 38.5, 10);
		RenderTextOnScreen(meshList[GEO_TEXT], PauseOption[startScreenArrow], Color(1, 0, 0), 4, 23, 15);
		modelStack.PopMatrix();
	}

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

