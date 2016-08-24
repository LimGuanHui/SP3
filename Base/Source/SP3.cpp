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

    gameState = Menu;
    gameStage = Normal;

	//B_battle = new BossBattle::Boss_Battle();
	//B_battle->Init();
    mapEditor = CreateNewMapEditorInstance();
    mapEditor->Init(Vector3(10,90,0));
    collision = CreateNewCollisionInstance();
    
    //Menu
	InputDelayTimer = 0;
	firingDebounce = 0;
	Fire = false;
	chargeTime = 0;
	chargeFire = false;

	Character = N_Character();
	AI = N_AI();

	Character->Movement->SetAnimationCounter(0);
	Character->Movement->SetPos_X(25);
	Character->Movement->SetPos_Y(20);

	Character->AI->Monster->Movement->SetPos_X(60);
	Character->AI->Monster->Movement->SetPos_Y(2);

	sceneSoundEngine = createIrrKlangDevice();

    collision->Init(Character, mapEditor);

	Play.Init(&m_goList);

    //mapEditor->LoadFromFile("Map1.csv");
    mapEditor->LoadFromFile("Map1.csv");
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
    collision->CheckCollision();


    Character->Movement->jumpUpdate(dt);
    
	if (Application::IsKeyPressed('H'))
	{
		Character->Attribute->SetReceivedDamage(10);
	}

    if (InputDelayTimer > 0)
        InputDelayTimer -= dt;

	if (Application::IsKeyPressed('A'))
	{
		Character->Movement->MoveLeftRight(true, 0.5f);
	}
	else if (Application::IsKeyPressed('D'))
	{
		Character->Movement->MoveLeftRight(false, 0.5f);
	}
    else
    {
        Character->Movement->SetVel_X(0);
    }

	/*if (Application::IsKeyPressed(' ') && InputDelayTimer <= 0)
	{
		InputDelayTimer = InputDelay;
		Character->Movement->SetToJump(true);
		std::cout << Character->Movement->GetPos_Y() << std::endl;
	}*/



	firingDebounce += (float)dt;

	bool KeyDown = false;
	bool check1 = false;
	bool check2 = false;

	if (Application::IsKeyPressed('Z') && firingDebounce > 1.f / fireRate)
	{
		KeyDown = false;
		firingDebounce = 0;
		Character->Movement->ProjectileUpdate(2.f, dt, 1);
	}
	if (Application::IsKeyPressed('X') && !KeyDown)
	{
		chargeTime += 2 * dt;
		if (chargeTime > 1)
		{
			chargeFire = true;
			KeyDown = true;
		}
	}
	if (!Application::IsKeyPressed('X'))
	{
		chargeTime = 0;
	}
	if (KeyDown && chargeFire)
	{
		chargeFire = false;
		KeyDown = false;
		chargeTime = 0;
		Character->Movement->ProjectileUpdate(2.f, dt, 7);
	}

//	std::cout << Character->Movement->Drop << " " << Character->Movement->InAir << std::endl;


	//std::cout << Character->Movement->Projectile->pos << std::endl;
	//std::cout << Character->Movement->GetPos_X() << Character->Movement->GetPos_Y() << std::endl;

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

	for (std::vector<PROJECTILE::Projectile *>::iterator it = Character->Movement->m_projectileList.begin(); it != Character->Movement->m_projectileList.end(); ++it)
	{
		PROJECTILE::Projectile *projectile = (PROJECTILE::Projectile *)*it;
		if (projectile->active)
		{
			projectile->pos += projectile->vel * dt;
		}
	}
    
    switch (gameState)
    {
    case SP3::EditMode:
        //map editor update
        mapEditor->Update(dt, CheckMousepos() + camera.position);
        if (Application::IsKeyPressed(VK_ESCAPE))
        {
            gameState = Game;
        }
        break;

	case SP3::Menu:
		if (Play.isClick == true && InputDelayTimer <= 0)
		{
			InputDelayTimer = InputDelay;
			switch (Play.button->type)
			{
			case(GameObject::GO_PLAYHOVER) :
				gameState = Game;
				break;
			case(GameObject::GO_LOADHOVER) :

				break;	
			case(GameObject::GO_EDITHOVER) :
				gameState = EditMode;
				break;
			case(GameObject::GO_EXITHOVER) :
				quitGame = true;
				break;
			}
			sceneSoundEngine->play2D("Sound/menu_enter.ogg");
		}

    case SP3::Pause:
		if (Play.isClick == true && InputDelayTimer <= 0)
		{
			InputDelayTimer = InputDelay;
			switch (Play.button->type)
			{
			case(GameObject::GO_PLAYHOVER) :
				gameState = Game;
				break;
			case(GameObject::GO_MENUHOVER) :
				gameState = Menu;
				break;
			case(GameObject::GO_EXITHOVER) :
				quitGame = true;
				break;
			}
			sceneSoundEngine->play2D("Sound/menu_enter.ogg");
		}
		break;

	case SP3::Game:
        
		if (Application::IsKeyPressed('I') && InputDelayTimer <= 0)
		{
			playerDead = true;
		}
		if (playerDead == true)
		{
			if (Play.isClick == true && InputDelayTimer <= 0)
				{
					InputDelayTimer = InputDelay;
					switch (Play.button->type)
					{
					case(GameObject::GO_RESTARTHOVER) :
						playerDead = false;
						gameState = Game;
						break;
					case(GameObject::GO_MENUHOVER) :
						playerDead = false;
						gameState = Menu;
						break;
					case(GameObject::GO_EXITHOVER) :
						quitGame = true;
						break;
					}
					sceneSoundEngine->play2D("Sound/menu_enter.ogg");
				}
			}

			if (Application::IsKeyPressed('P') && InputDelayTimer <= 0)
			{
				InputDelayTimer = InputDelay;
				gameState = Pause;
			}

			if (Application::IsKeyPressed('O') && InputDelayTimer <= 0)
			{
				InputDelayTimer = InputDelay;
				gameState = End;
			}

			
			// Camera Panning to Character position & stuff
			/*if (Character->Movement->GetPos_X() > 150 + camera.position.x)
			{
				camera.position.x += dt * camera.CAM_SPEED;
				camera.target.x += dt * camera.CAM_SPEED;
			}
			else if (Character->Movement->GetPos_X() < 20 + camera.position.x)
			{
				camera.position.x -= dt * camera.CAM_SPEED;
				camera.target.x -= dt * camera.CAM_SPEED;
			}

			if (Character->Movement->GetPos_Y() > 80 +  camera.position.y)
			{
				camera.position.y += dt * camera.CAM_SPEED;
				camera.target.y += dt * camera.CAM_SPEED;
			}
			else if (Character->Movement->GetPos_Y() < 5 +  camera.position.y)
			{
				camera.position.y -= dt * camera.CAM_SPEED;
				camera.target.y -= dt * camera.CAM_SPEED;
			}*/

			break;
	case SP3::Transition:
		//Transition here
		break;

	case SP3::End:
		if (Play.isClick == true && InputDelayTimer <= 0)
		{
			InputDelayTimer = InputDelay;
			switch (Play.button->type)
			{
			case(GameObject::GO_MENUHOVER) :
				gameState = Menu;
				break;
				
			case(GameObject::GO_EXITHOVER) :
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
	Play.Update(CheckMousepos() + camera.position, dt, &m_goList);
	camera.Update(dt);
}

void SP3::RenderGO(GameObject *go)
{
    
    //rotate code
    modelStack.Rotate(Math::RadianToDegree(atan2(-go->vel.x, go->vel.y)), 0, 0, 1);
    

   modelStack.PushMatrix();
    Vector3 temp;
    switch (go->type)
    {
	case(GameObject::GO_PLAY) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_PLAY], false);
		break;

	case(GameObject::GO_PLAYHOVER) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_PLAYHOVER], false);
		break;

	case(GameObject::GO_MENU) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_MENU], false);
		break;

	case(GameObject::GO_MENUHOVER) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_MENUHOVER], false);
		break;

	case(GameObject::GO_EDIT) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_EDIT], false);
		break;

	case(GameObject::GO_EDITHOVER) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_EDITHOVER], false);
		break;

	case(GameObject::GO_LOAD) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_LOAD], false);
		break;

	case(GameObject::GO_LOADHOVER) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_LOADHOVER], false);
		break;

	case(GameObject::GO_HIGHSCORE) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_HIGHSCORE], false);
		break;

	case(GameObject::GO_HIGHSCOREHOVER) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_HIGHSCOREHOVER], false);
		break;

	case(GameObject::GO_SAVE) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_SAVE], false);
		break;

	case(GameObject::GO_SAVEHOVER) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_SAVEHOVER], false);
		break;

	case(GameObject::GO_EXIT) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_EXIT], false);
		break;

	case(GameObject::GO_EXITHOVER) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_EXITHOVER], false);
		break;

	case(GameObject::GO_RESTART) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_RESTART], false);
		break;

	case(GameObject::GO_RESTARTHOVER) :
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_RESTARTHOVER], false);
		break;


    default:
        break;
    }
    modelStack.PopMatrix();

}

void SP3::RenderProjectile(PROJECTILE::Projectile *projectile)
{
	if (Character->Movement->GetAnimationInvert() == false)
	{
		modelStack.PushMatrix();
		modelStack.Translate(projectile->pos.x, projectile->pos.y, 0);
		modelStack.Scale(projectile->scale.x, projectile->scale.y, projectile->scale.z);
		RenderMesh(meshList[GEO_PROJECTILE], false);
		modelStack.PopMatrix();
	}
	else if (Character->Movement->GetAnimationInvert() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(projectile->pos.x, projectile->pos.y, 0);
		modelStack.Scale(projectile->scale.x, projectile->scale.y, projectile->scale.z);
		modelStack.Rotate(180, 0, 0, 1);
		RenderMesh(meshList[GEO_PROJECTILE], false);
		modelStack.PopMatrix();
	}
	
}

void SP3::RenderUI()
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

    //rendering of stuffs
    RenderFromList(test_B_battle,mapEditor);

    std::ostringstream ss;
    ss.str(string());
    ss.precision(5);
    ss << "FPS: " << fps;
   // RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 0);

    RenderText();

	if (gameState == Menu)
	{
		modelStack.PushMatrix();
		RenderModelOnScreen(meshList[GEO_PLAYERHP], false, Vector3(Character->Attribute->GetCurrentHP() * 0.2f, 2.f, 0.f), 50.f - (157.f - (float)Character->Attribute->GetCurrentHP())*0.1f, 57.7f, 1.f, Vector3(0.f, 0.f, 0.f));
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2 + camera.position.x, m_worldHeight / 2 + camera.position.y, -1.f);
		modelStack.Scale(180, 110, 0);
		RenderMesh(meshList[GEO_UI], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(10.f + camera.position.x, 10.f + camera.position.y, 0.f);
		modelStack.Scale(10.f, 13.f, 0.f);
		RenderMesh(meshList[GEO_PRINCESS], false);
		modelStack.PopMatrix();

		Play.PlayButton->active = true;
		Play.PlayButton->pos.Set(m_worldWidth / 2 + camera.position.x, (m_worldHeight - 30) / 2 + camera.position.y, 1.f);
		Play.EditButton->active = true;
		Play.EditButton->pos.Set(m_worldWidth / 2 + camera.position.x, (m_worldHeight - 55) / 2 + camera.position.y, 1.f);
		Play.LoadButton->active = true;
		Play.LoadButton->pos.Set(m_worldWidth / 2 + camera.position.x, (m_worldHeight - 80) / 2 + camera.position.y, 1.f);
		Play.ExitButton->active = true;
		Play.ExitButton->pos.Set(16.f + camera.position.x, 94.f + camera.position.y, 1.f);

		Play.MenuButton->active = false;
		Play.MenuButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		Play.RestartButton->active = false;
		Play.RestartButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
	}
	if (gameState == Game)
	{
        
		Play.PlayButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		Play.EditButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		Play.LoadButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		Play.ExitButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		Play.RestartButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		Play.MenuButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		Play.SaveButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);

		if (playerDead == true)
		{
			Play.RestartButton->active = true;
			Play.RestartButton->pos.Set(m_worldWidth / 2 + camera.position.x, (m_worldHeight - 30.f) / 2 + camera.position.y, 1.f);
			Play.MenuButton->active = true;
			Play.MenuButton->pos.Set(m_worldWidth / 2 + camera.position.x, (m_worldHeight - 60.f) / 2 + camera.position.y, 1.f);
			Play.ExitButton->active = true;
			Play.ExitButton->pos.Set(16.f + camera.position.x, 94.f + camera.position.y, 1.f);

			modelStack.PushMatrix();
			modelStack.Translate(m_worldWidth / 2 + camera.position.x, m_worldHeight / 2 + camera.position.y, -1.f);
			modelStack.Scale(180, 110, 0);
			RenderMesh(meshList[GEO_DEATHSCREEN], false);
			modelStack.PopMatrix();

			Play.EditButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
			Play.LoadButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
			Play.PlayButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		}

		RenderCharacter();

		for (std::vector<PROJECTILE::Projectile *>::iterator it = Character->Movement->m_projectileList.begin(); it != Character->Movement->m_projectileList.end(); ++it)
		{
			PROJECTILE::Projectile *projectile = (PROJECTILE::Projectile *)*it;
			if (projectile->active)
			{
				RenderProjectile(projectile);
			}
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
	if (gameState == Pause)
	{
		Play.LoadButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		Play.EditButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);

		Play.PlayButton->active = true;
		Play.PlayButton->pos.Set(m_worldWidth / 2 + camera.position.x, (m_worldHeight - 30.f) / 2 + camera.position.y, 1.f);
		Play.MenuButton->active = true;
		Play.MenuButton->pos.Set(m_worldWidth / 2 + camera.position.x, (m_worldHeight - 60.f) / 2 + camera.position.y, 1.f);
		Play.ExitButton->active = true;
		Play.ExitButton->pos.Set(16.f + camera.position.x, 94.f + camera.position.y, 1.f);

		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2 + camera.position.x, m_worldHeight / 2 + camera.position.y, -1.f);
		modelStack.Scale(180, 110, 0);
		RenderMesh(meshList[GEO_PAUSEUI], false);
		modelStack.PopMatrix();
	}
	if (gameState == End)
	{
		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2 + camera.position.x, m_worldHeight / 2 + camera.position.y, -1.f);
		modelStack.Scale(180, 110, 0);
		RenderMesh(meshList[GEO_VICTORY], false);
		modelStack.PopMatrix();

		Play.PlayButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		Play.EditButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		Play.LoadButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		Play.RestartButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);

		Play.MenuButton->active = true;
		Play.MenuButton->pos.Set(m_worldWidth / 2 + camera.position.x, (m_worldHeight - 30.f) / 2 + camera.position.y, 1.f);

		Play.ExitButton->active = true;
		Play.ExitButton->pos.Set(m_worldWidth / 2 + camera.position.x, (m_worldHeight - 60.f) / 2 + camera.position.y, 1.f);
	}
	if (gameState == EditMode)
	{
		Play.PlayButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		Play.EditButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		Play.LoadButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		Play.ExitButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		Play.RestartButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		Play.MenuButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);
		Play.SaveButton->pos.Set(-20 + camera.position.x, -20 + camera.position.y, 1);

		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2 + camera.position.x, m_worldHeight / 2 + camera.position.y, -1.f);
		modelStack.Scale(180, 110, 0);
		RenderMesh(meshList[GEO_EDITBACKGROUND], false);
		modelStack.PopMatrix();
	}

	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active)
		{
			RenderGO(go);
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
  //ss << "FPS: " << Play.button->type;
  //RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 0);

    RenderUI();
    RenderCharacter();
    RenderText();
    RenderEditorSelector(mapEditor->curr);

	for (std::vector<PROJECTILE::Projectile *>::iterator it = Character->Movement->m_projectileList.begin(); it != Character->Movement->m_projectileList.end(); ++it)
	{
		PROJECTILE::Projectile *projectile = (PROJECTILE::Projectile *)*it;
		if (projectile->active)
		{
			RenderProjectile(projectile);
		}
	}
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

    /*for (std::vector<Platform *>::iterator it = map_editor->Platform_List.begin(); it != map_editor->Platform_List.end(); ++it)
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
    }*/
    if (gameState == Game)
    {
        int rowct = 0;
        for (int i = map_editor->Tilemap.size() - 1; i > 0; i--)//row
        {
            for (int i2 = 0; i2 < map_editor->Tilemap[i].size(); i2++)//col
            {
                modelStack.PushMatrix();
                modelStack.Translate((i2) * (m_worldWidth / 44) ,
                    (rowct + 1)* (m_worldHeight / 25)
                    , 0);
                modelStack.Scale(4,4,4);
                switch (map_editor->Tilemap[i][i2])
                {
                case 0:
                    break;
                case 1:
                    RenderMesh(meshList[GEO_PLAT_NORMAL], false);
                    break;
                default:
                    break;
                }
                modelStack.PopMatrix();
            }
            rowct++;
        }
    }
    if (gameState == EditMode)
    {
        for (std::vector<Platform *>::iterator it = mapEditor->Platform_Display_List.begin(); it != mapEditor->Platform_Display_List.end(); ++it)
        {
            Platform *go = (Platform *)*it;
            modelStack.PushMatrix();
            modelStack.Translate(go->getpos().x, go->getpos().y, go->getpos().z);
            modelStack.Scale(go->getscale().x, go->getscale().y, go->getscale().z);
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
    else if (gameState == Game)
    {
        for (std::vector<Platform *>::iterator it = mapEditor->Platform_List.begin(); it != mapEditor->Platform_List.end(); ++it)
        {
            Platform *go = (Platform *)*it;
            modelStack.PushMatrix();
            modelStack.Translate(go->getpos().x, go->getpos().y, go->getpos().z);
            modelStack.Scale(go->getscale().x, go->getscale().y, go->getscale().z);
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

    /*std::ostringstream ss;
    ss.str(string());
    ss.precision(5);
    ss << "cam pos: " << camera.position;
    RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 0, 1), 2.f, 0, 23);*/
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
    std::ostringstream ss;
    switch (gameState)
    {
    case SP3::EditMode:
        RenderTextOnScreen(meshList[GEO_TEXT], mapEditor->TextForDisplay(), Color(0, 0, 1), 2.f, 0, 2);
        
        {
            ss.str(string());
            ss.precision(5);
            ss << "mousepos: " << CheckMousepos();
            RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 0, 1), 2.f, 0, 4);
        }
        if (mapEditor->edit_state == mapEditor->SAVE || mapEditor->edit_state == mapEditor->LOAD)
        {
            ss.str(string());
            ss.precision(5);
            ss << "selected file: " << mapEditor->getSelectedFile();
            RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 0, 1), 2.f, 0, 6);
        }
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

void SP3::RenderEditorSelector(Platform* curr)
{
    if (mapEditor->edit_state == Map_Editor::MANAGE)
    {
        modelStack.PushMatrix();
        Vector3 temp = mapEditor->curr->getpos();
        modelStack.Translate(curr->getpos().x, curr->getpos().y, curr->getpos().z);
        modelStack.Scale(curr->getscale().x + 8, curr->getscale().y + 8, curr->getscale().z + 8);
        RenderMesh(meshList[GEO_PLAT_SELECTOR], false);
        modelStack.PopMatrix();
    }
}

void SP3::RenderCharacter()
{
	if (Character->Movement->GetAnimationInvert() == false)
	{
		if (Character->Movement->GetAnimationCounter() == 0)
		{
			modelStack.PushMatrix();
			modelStack.Translate(Character->Movement->GetPos_X(), Character->Movement->GetPos_Y(), 0);
            modelStack.Scale(Character->Movement->GetScale_X(), Character->Movement->GetScale_Y(), 1);
			RenderMesh(meshList[GEO_CHARACTER], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(Character->AI->Monster->Movement->GetPos_X(), Character->AI->Monster->Movement->GetPos_Y(), 0);
			modelStack.Scale(10, 10, 10);
			RenderMesh(meshList[GEO_MONSTER2], false);
			modelStack.PopMatrix();

		}
		if (Character->Movement->GetAnimationCounter() == 1)
		{
			modelStack.PushMatrix();
			modelStack.Translate(Character->Movement->GetPos_X(), Character->Movement->GetPos_Y(), 0);
            modelStack.Scale(Character->Movement->GetScale_X(), Character->Movement->GetScale_Y(), 1);
			RenderMesh(meshList[GEO_CHARACTER], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(Character->AI->Monster->Movement->GetPos_X(), Character->AI->Monster->Movement->GetPos_Y(), 0);
			modelStack.Scale(10, 10, 10);
			RenderMesh(meshList[GEO_MONSTER2], false);
			modelStack.PopMatrix();
		}
		if (Character->Movement->GetAnimationCounter() == 2)
		{
			modelStack.PushMatrix();
			modelStack.Translate(Character->Movement->GetPos_X(), Character->Movement->GetPos_Y(), 0);
            modelStack.Scale(Character->Movement->GetScale_X(), Character->Movement->GetScale_Y(), 1);
            RenderMesh(meshList[GEO_CHARACTER], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(Character->AI->Monster->Movement->GetPos_X(), Character->AI->Monster->Movement->GetPos_Y(), 0);
			modelStack.Scale(10, 10, 10);
			RenderMesh(meshList[GEO_MONSTER2], false);
			modelStack.PopMatrix();
		}
	}
	else if (Character->Movement->GetAnimationInvert() == true)
	{
		if (Character->Movement->GetAnimationCounter() == 0)
		{
			modelStack.PushMatrix();
			modelStack.Translate(Character->Movement->GetPos_X(), Character->Movement->GetPos_Y(), 0);
            modelStack.Scale(Character->Movement->GetScale_X(), Character->Movement->GetScale_Y(), 1);
            RenderMesh(meshList[GEO_CHARACTER2], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(Character->AI->Monster->Movement->GetPos_X(), Character->AI->Monster->Movement->GetPos_Y(), 0);
			modelStack.Scale(10, 10, 10);
			RenderMesh(meshList[GEO_MONSTER], false);
			modelStack.PopMatrix();
		}
		if (Character->Movement->GetAnimationCounter() == 1)
		{
			modelStack.PushMatrix();
			modelStack.Translate(Character->Movement->GetPos_X(), Character->Movement->GetPos_Y(), 0);
            modelStack.Scale(Character->Movement->GetScale_X(), Character->Movement->GetScale_Y(), 1);
            RenderMesh(meshList[GEO_CHARACTER2], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(Character->AI->Monster->Movement->GetPos_X(), Character->AI->Monster->Movement->GetPos_Y(), 0);
			modelStack.Scale(10, 10, 10);
			RenderMesh(meshList[GEO_MONSTER], false);
			modelStack.PopMatrix();
		}
		if (Character->Movement->GetAnimationCounter() == 2)
		{
			modelStack.PushMatrix();
			modelStack.Translate(Character->Movement->GetPos_X(), Character->Movement->GetPos_Y(), 0);
            modelStack.Scale(Character->Movement->GetScale_X(), Character->Movement->GetScale_Y(), 1);
            RenderMesh(meshList[GEO_CHARACTER2], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(Character->AI->Monster->Movement->GetPos_X(), Character->AI->Monster->Movement->GetPos_Y(), 0);
			modelStack.Scale(10, 10, 10);
			RenderMesh(meshList[GEO_MONSTER], false);
			modelStack.PopMatrix();
		}
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

