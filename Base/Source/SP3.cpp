#include "SP3.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>
#define InputDelay 0.1f

SP3::SP3()
{
   // sceneSoundEngine = NULL;
}

SP3::~SP3()
{
   // if (sceneSoundEngine != NULL)
   // {
   //     sceneSoundEngine->drop();
   // }
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


    //Mob* testMob = CreateMob(5.0f);
    //testMob->Init();

    test_B_battle = CreateBossBattleInstance();
    //test_B_battle->Init(Vector3(10.5,11.25f,0.f));

	quitGame = false;
	playerDead = false;

	option = First;
	option2 = First2;
	option3 = First3;

    gameState = Menu;
    gameStage = Normal;

	//B_battle = new BossBattle::Boss_Battle();
	//B_battle->Init();
    mapEditor = CreateNewMapEditorInstance();
    mapEditor->Init();

    //Menu
	InputDelayTimer = 0;
	Character = N_Character();

	sceneSoundEngine = createIrrKlangDevice();
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
        //map editor update
        mapEditor->Update(dt, CheckMousepos());
        break;

	case SP3::Menu:
		if (Application::IsKeyPressed(VK_DOWN) && InputDelayTimer <= 0)
		{
			InputDelayTimer = InputDelay;
			if (selectArrow != (NUM3 - 1))
				selectArrow++;
			else
				selectArrow = 0;
			sceneSoundEngine->play2D("Sound/menu_updown.ogg");
		}
		if (Application::IsKeyPressed(VK_UP) && InputDelayTimer <= 0)
		{
			InputDelayTimer = InputDelay;
			if (selectArrow != 0)
				selectArrow--;
			else
				selectArrow = NUM3 - 1;
			sceneSoundEngine->play2D("Sound/menu_updown.ogg");
		}
		if (Application::IsKeyPressed(VK_RETURN) && InputDelayTimer <= 0)
		{
			InputDelayTimer = InputDelay;
			switch (selectArrow)
			{
			case(Start) :
				gameState = Game;
				break;
			case(Load) :
				
				break;
			case(Edit) :
				gameState = EditMode;
				break;
			case(Quit) :
				quitGame = true;
				break;
			}
			sceneSoundEngine->play2D("Sound/menu_enter.ogg");
		}
		if (Application::IsKeyPressed('0') && InputDelayTimer <= 0)
		{
			InputDelayTimer = InputDelay;
			gameState = EditMode;
		}
		break;

    case SP3::Pause:
		if (Application::IsKeyPressed(VK_DOWN) && InputDelayTimer <= 0)
		{
			InputDelayTimer = InputDelay;
			if (selectArrow2 != (NUM4 - 1))
				selectArrow2++;
			else
				selectArrow2 = 0;
			sceneSoundEngine->play2D("Sound/menu_updown.ogg");
		}
		if (Application::IsKeyPressed(VK_UP) && InputDelayTimer <= 0)
		{
			InputDelayTimer = InputDelay;
			if (selectArrow2 != 0)
				selectArrow2--;
			else
				selectArrow2 = NUM4 - 1;
			sceneSoundEngine->play2D("Sound/menu_updown.ogg");
		}
		if (Application::IsKeyPressed(VK_RETURN) && InputDelayTimer <= 0)
		{
			InputDelayTimer = InputDelay;
			switch (selectArrow2)
			{
			case(Resume) :
				gameState = Game;
				break;
			case(Menu2) :
				gameState = Menu;
				break;
			case(Quit2) :
				quitGame = true;
				break;
			}
			sceneSoundEngine->play2D("Sound/menu_enter.ogg");
		}
		break;

	case SP3::Game:
		if (Application::IsKeyPressed(' ') && InputDelayTimer <= 0)
		{
			playerDead = true;
		}
		if (playerDead == true)
		{
			if (Application::IsKeyPressed(VK_DOWN) && InputDelayTimer <= 0)
			{
				InputDelayTimer = InputDelay;
				if (selectArrow3 != (NUM5 - 1))
					selectArrow3++;
				else
					selectArrow3 = 0;
				sceneSoundEngine->play2D("Sound/menu_updown.ogg");
			}
			if (Application::IsKeyPressed(VK_UP) && InputDelayTimer <= 0)
			{
				InputDelayTimer = InputDelay;
				if (selectArrow3 != 0)
					selectArrow3--;
				else
					selectArrow3 = NUM5 - 1;
				sceneSoundEngine->play2D("Sound/menu_updown.gg");
			
			}
			if (Application::IsKeyPressed(VK_RETURN) && InputDelayTimer <= 0)
				{
					InputDelayTimer = InputDelay;
					switch (selectArrow3)
					{
					case(Restart) :
						playerDead = false;
						gameState = Game;
						break;
					case(Menu3) :
						playerDead = false;
						gameState = Menu;
						break;
					case(Quit3) :
						quitGame = true;
						break;
					}
					sceneSoundEngine->play2D("Sound/menu_enter.ogg");
				}
			}

			if (Application::IsKeyPressed('P'))
			{
				gameState = Pause;
			}

			if (Application::IsKeyPressed('O'))
			{
				gameState = End;
			}

			break;
	case SP3::Transition:
		//Transition here
		break;

	case SP3::End:
		if (Application::IsKeyPressed(VK_DOWN) && InputDelayTimer <= 0)
		{
			InputDelayTimer = InputDelay;
			if (selectArrow4 != (NUM7 - 1))
				selectArrow4++;
			else
				selectArrow4 = 0;
			sceneSoundEngine->play2D("Sound/menu_updown.ogg");
		}
		if (Application::IsKeyPressed(VK_UP) && InputDelayTimer <= 0)
		{
			InputDelayTimer = InputDelay;
			if (selectArrow4 != 0)
				selectArrow4--;
			else
				selectArrow4 = NUM7 - 1;
			sceneSoundEngine->play2D("Sound/menu_updown.gg");

		}
		if (Application::IsKeyPressed(VK_RETURN) && InputDelayTimer <= 0)
		{
			InputDelayTimer = InputDelay;
			switch (selectArrow4)
			{
			case(Menu4) :
				gameState = Menu;
				break;
				
			case(Quit4) :
				quitGame = true;
				break;
			}
			sceneSoundEngine->play2D("Sound/menu_enter.ogg");
		}
		break;

	default:
		break;

	}
	switch (gameStage)
	{
	case SP3::Normal:
		break;

	case SP3::Boss:
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

void SP3::RenderUI()
{
	if (gameState == Game)
	{
		if (playerDead == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(66.f, 50.f, 0);
			modelStack.Scale(140, 107, 0);
			RenderMesh(meshList[GEO_DEATHSCREEN], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Restart", Color(1, 1, 1), 4, 29, 16);
			RenderTextOnScreen(meshList[GEO_TEXT], "Main Menu", Color(1, 1, 1), 4, 26, 12);
			RenderTextOnScreen(meshList[GEO_TEXT], "Quit Game", Color(1, 1, 1), 4, 26, 8);
			modelStack.PopMatrix();

			switch (selectArrow3)
			{
			case(First3) :
				modelStack.PushMatrix();
				modelStack.Translate(42, 30.5, 1);
				modelStack.Scale(10, 10, 10);
				RenderMesh(meshList[GEO_RESTARTCURSOR], false);
				modelStack.PopMatrix();
				break;

			case(Second3) :
				modelStack.PushMatrix();
				modelStack.Translate(38, 24, 1);
				modelStack.Scale(10, 10, 10);
				RenderMesh(meshList[GEO_MENUCURSOR], false);
				modelStack.PopMatrix();
				break;

			case(Third3) :
				modelStack.PushMatrix();
				modelStack.Translate(38, 17, 1);
				modelStack.Scale(10, 10, 10);
				RenderMesh(meshList[GEO_QUITCURSOR], false);
				modelStack.PopMatrix();
				break;
			}
		}
	}

	if (gameState == Menu)
	{
		modelStack.PushMatrix();
		modelStack.Translate(65.f, 50.f, -1.f);
		modelStack.Scale(140, 107, 0);
		RenderMesh(meshList[GEO_UI], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Welcome", Color(0, 0, 1), 4, 31, 50);
		RenderTextOnScreen(meshList[GEO_TEXT], "To", Color(0, 0, 1), 4, 38, 45);
		RenderTextOnScreen(meshList[GEO_TEXT], "Suk Malcolm Deek", Color(0, 0, 1), 4, 19, 40);
		RenderTextOnScreen(meshList[GEO_TEXT], "Start Game", Color(1, 0, 0), 4, 27, 20);
		RenderTextOnScreen(meshList[GEO_TEXT], "Load Level", Color(1, 0, 0), 4, 27.5, 16);
		RenderTextOnScreen(meshList[GEO_TEXT], "Edit Level", Color(1, 0, 0), 4, 27.5, 12);
		RenderTextOnScreen(meshList[GEO_TEXT], "Quit Game", Color(1, 0, 0), 4, 28, 8.5);
		modelStack.PopMatrix();

		switch (selectArrow)
		{
		case(First) :
			modelStack.PushMatrix();
			modelStack.Translate(38, 36.5, 1);
			modelStack.Scale(10, 10, 10);
			RenderMesh(meshList[GEO_SELECT], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Start Game", Color(0, 1, 0), 4, 27, 20);
			modelStack.PopMatrix();
			break;
		case(Second) :
			modelStack.PushMatrix();
			modelStack.Translate(38, 30, 1);
			modelStack.Scale(10, 10, 10);
			RenderMesh(meshList[GEO_SELECT], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Load Level", Color(0, 1, 0), 4, 27.5, 16);
			modelStack.PopMatrix();
			break;
		case(Third) :
			modelStack.PushMatrix();
			modelStack.Translate(38, 23.5, 1);
			modelStack.Scale(10, 10, 10);
			RenderMesh(meshList[GEO_SELECT], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Edit Level", Color(0, 1, 0), 4, 27.5, 12);
			modelStack.PopMatrix();
			break;
		case(Fourth) :
			modelStack.PushMatrix();
			modelStack.Translate(38, 17, 1);
			modelStack.Scale(10, 10, 10);
			RenderMesh(meshList[GEO_SELECT], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Quit Game", Color(0, 1, 0), 4, 28, 8.5);
			modelStack.PopMatrix();
			break;
		}
	}

	if (gameState == Pause)
	{
		modelStack.PushMatrix();
		modelStack.Translate(65.f, 50.f, 0.f);
		modelStack.Scale(140, 107, 0);
		RenderMesh(meshList[GEO_UI], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Game Paused", Color(0, 0, 1), 4, 26, 40);
		RenderTextOnScreen(meshList[GEO_TEXT], "Resume", Color(1, 0, 0), 4, 33, 20);
		RenderTextOnScreen(meshList[GEO_TEXT], "Main Menu", Color(1, 0, 0), 4, 29, 16);
		RenderTextOnScreen(meshList[GEO_TEXT], "Quit Game", Color(1, 0, 0), 4, 29, 12);
		modelStack.PopMatrix();

		switch (selectArrow2)
		{
		case(First2) :
			modelStack.PushMatrix();
			modelStack.Translate(47, 36.5, 1);
			modelStack.Scale(10, 10, 10);
			RenderMesh(meshList[GEO_SELECT], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Resume", Color(0, 1, 0), 4, 33, 20);
			modelStack.PopMatrix();
			break;
		case(Second2) :
			modelStack.PushMatrix();
			modelStack.Translate(42, 30, 1);
			modelStack.Scale(10, 10, 10);
			RenderMesh(meshList[GEO_SELECT], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Main Menu", Color(0, 1, 0), 4, 29, 16);
			modelStack.PopMatrix();
			break;
		case(Third2) :
			modelStack.PushMatrix();
			modelStack.Translate(42, 23.5, 1);
			modelStack.Scale(10, 10, 10);
			RenderMesh(meshList[GEO_SELECT], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Quit Game", Color(0, 1, 0), 4, 29, 12);
			modelStack.PopMatrix();
			break;
		}
	}

	if (gameState == End)
	{
		modelStack.PushMatrix();
		modelStack.Translate(67.f, 50.f, -1.f);
		modelStack.Scale(140, 107, 0);
		RenderMesh(meshList[GEO_VICTORY], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Main Menu", Color(1, 0, 0), 4, 29, 16);
		RenderTextOnScreen(meshList[GEO_TEXT], "Quit Game", Color(1, 0, 0), 4, 29, 12);
		modelStack.PopMatrix();

		switch (selectArrow4)
		{
		case(First4) :
			modelStack.PushMatrix();
			modelStack.Translate(40, 30, 1);
			modelStack.Scale(10, 10, 10);
			RenderMesh(meshList[GEO_MENUCURSOR2], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Main Menu", Color(0, 1, 0), 4, 29, 16);
			modelStack.PopMatrix();
			break;

		case(Second4) :
			modelStack.PushMatrix();
			modelStack.Translate(40, 23.5, 1);
			modelStack.Scale(10, 10, 10);
			RenderMesh(meshList[GEO_QUITCURSOR2], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Quit Game", Color(0, 1, 0), 4, 29, 12);
			modelStack.PopMatrix();
			break;
		}
	}
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
    //rendering of stuffs
    for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
    {
        GameObject *go = (GameObject *)*it;
        if (go->active)
        {
            RenderGO(go);
        }
    }
    RenderFromList(test_B_battle,mapEditor);


    std::ostringstream ss;
    ss.str(string());
    ss.precision(5);
    ss << "FPS: " << fps;
   // RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 0);

	RenderUI();
    RenderText();

}
void SP3::RenderFromList(Boss_Battle* b_battle, Map_Editor* map_editor)
{
    modelStack.PushMatrix();
    
    for (std::vector<Panels::Panel *>::iterator it = b_battle->P_Panel_List.begin(); it != b_battle->P_Panel_List.end(); ++it)
    {
        Panels::Panel *go = (Panels::Panel *)*it;
        Vector3 temp = go->getpos();
        modelStack.PushMatrix();
        modelStack.Translate(temp.x, temp.y, temp.z);
        temp = go->getscale();
        modelStack.Scale(temp.x, temp.y, temp.z);

        switch (go->panel_pos)
        {
        case Panels::Panel::Bottom:
            RenderMesh(meshList[GEO_B_PANEL], false);
            break;
        case Panels::Panel::Middle:
            RenderMesh(meshList[GEO_M_PANEL], false);
            break;
        case Panels::Panel::Top:
            RenderMesh(meshList[GEO_T_PANEL], false);
            break;
        default:
            break;
        }
        modelStack.PopMatrix();
    }
    modelStack.PopMatrix();

    for (std::vector<Platform *>::iterator it = map_editor->Platform_List.begin(); it != map_editor->Platform_List.end(); ++it)
    {
        Platform* go = (Platform*)*it;
        Vector3 temp = go->getpos();
        modelStack.PushMatrix();
        modelStack.Translate(temp.x, temp.y, temp.z);
        temp = go->getscale();
        modelStack.Scale(temp.x, temp.y, temp.z);
        switch (go->type)
        {
        case Platform::Normal:
            RenderMesh(meshList[GEO_PLAT_NORMAL], false);
            break;
        default:
            break;
        }
        modelStack.PopMatrix();
    }
}

Vector3 SP3::CheckMousepos()
{
    float m_worldHeight = 100.f;
    float m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();


    double x, y;
    Application::GetCursorPos(&x, &y);
    int w = Application::GetWindowWidth();
    int h = Application::GetWindowHeight();
    float worldX = x * m_worldWidth / w;
    float worldY = (h - y) * m_worldHeight / h;

    return Vector3(worldX, worldY, 0);
}

void SP3::RenderText()
{
    switch (gameState)
    {
    case SP3::EditMode:
        RenderTextOnScreen(meshList[GEO_TEXT], mapEditor->TextForDisplay(), Color(1, 1, 1), 2.f, 0, 2);
        break;
	case SP3::Menu:
        
        break;
    case SP3::Pause:
        break;
    case SP3::Game:
        break;
    case SP3::Transition:
        break;
    case SP3::End:
        break;
    default:
        break;
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

