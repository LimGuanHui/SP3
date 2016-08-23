#include "Buttons.h"
#include <Windows.h>

Buttons::Buttons()
{
	isClick = false;
}

Buttons::~Buttons()
{

}

void Buttons::Init(vector<GameObject *>* buttonList)
{
	PlayButton = new GameObject();
	PlayButton->type = GameObject::GO_PLAY;
	PlayButton->pos.Set(-20.f + camera.position.x, -20.f + camera.position.y, 1.f);
	PlayButton->scale.Set(20.f, 15.f, 20.f);
	PlayButton->active = false;
	buttonList->push_back(PlayButton);

	MenuButton = new GameObject();
	MenuButton->type = GameObject::GO_MENU;
	MenuButton->pos.Set(-20.f + camera.position.x, -20.f + camera.position.y, 1.f);
	MenuButton->scale.Set(20.f, 15.f, 20.f);
	MenuButton->active = false;
	buttonList->push_back(MenuButton);

	EditButton = new GameObject();
	EditButton->type = GameObject::GO_EDIT;
	EditButton->pos.Set(-20.f + camera.position.x, -20.f + camera.position.y, 1.f);
	EditButton->scale.Set(20.f, 15.f, 20.f);
	EditButton->active = false;
	buttonList->push_back(EditButton);

	LoadButton = new GameObject();
	LoadButton->type = GameObject::GO_LOAD;
	LoadButton->pos.Set(-20.f + camera.position.x, -20.f + camera.position.y, 1.f);
	LoadButton->scale.Set(20.f, 15.f, 20.f);
	LoadButton->active = false;
	buttonList->push_back(LoadButton);

	HighscoreButton = new GameObject();
	HighscoreButton->type = GameObject::GO_HIGHSCORE;
	HighscoreButton->pos.Set(-20.f + camera.position.x, -20.f + camera.position.y, 1.f);
	HighscoreButton->scale.Set(20.f, 15.f, 20.f);
	HighscoreButton->active = false;
	buttonList->push_back(HighscoreButton);

	SaveButton = new GameObject();
	SaveButton->type = GameObject::GO_SAVE;
	SaveButton->pos.Set(-20.f + camera.position.x, -20.f + camera.position.y, 1.f);
	SaveButton->scale.Set(20.f, 15.f, 20.f);
	SaveButton->active = false;
	buttonList->push_back(SaveButton);

	ExitButton = new GameObject();
	ExitButton->type = GameObject::GO_EXIT;
	ExitButton->pos.Set(-20.f + camera.position.x, -20.f + camera.position.y, 1.f);
	ExitButton->scale.Set(20.f, 15.f, 20.f);
	ExitButton->active = false;
	buttonList->push_back(ExitButton);

	RestartButton = new GameObject();
	RestartButton->type = GameObject::GO_RESTART;
	RestartButton->pos.Set(-20.f + camera.position.x, -20.f + camera.position.y, 1.f);
	RestartButton->scale.Set(20.f, 15.f, 20.f);
	RestartButton->active = false;
	buttonList->push_back(RestartButton);

}

void Buttons::Update(Vector3 mousepos, float dt, vector<GameObject *>* buttonList)
{
	isClick = false;
	for (vector<GameObject *>::iterator it = buttonList->begin(); it != buttonList->end(); ++it)
	{
		GameObject *go1 = (GameObject *)*it;
		float distanceSquared = ((go1->pos) - (mousepos)).LengthSquared();
		float combinedRadiusSquared = (go1->scale.x - 10.f) * (go1->scale.x - 10.f);
		Vector3 relativeDisplacement = mousepos - go1->pos;
		if (distanceSquared < combinedRadiusSquared)
		{
			MouseHover(go1);
			if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
			{
				isClick = true;
				button = go1;
			}
			continue;
		}
		else
		{
			switch (go1->type)
			{
			case(GameObject::GO_PLAYHOVER) :
				go1->type = GameObject::GO_PLAY;
				go1->scale.Set(20.f, 15.f, 20.f);
				break;

			case(GameObject::GO_MENUHOVER) :
				go1->type = GameObject::GO_MENU;
				go1->scale.Set(20.f, 15.f, 20.f);
				break;

			case(GameObject::GO_EDITHOVER) :
				go1->type = GameObject::GO_EDIT;
				go1->scale.Set(20.f, 15.f, 20.f);
				break;

			case(GameObject::GO_LOADHOVER) :
				go1->type = GameObject::GO_LOAD;
				go1->scale.Set(20.f, 15.f, 20.f);
				break;

			case(GameObject::GO_HIGHSCOREHOVER) :
				go1->type = GameObject::GO_HIGHSCORE;
				go1->scale.Set(20.f, 15.f, 20.f);
				break;

			case(GameObject::GO_SAVEHOVER) :
				go1->type = GameObject::GO_SAVE;
				go1->scale.Set(20.f, 15.f, 20.f);
				break;

			case(GameObject::GO_EXITHOVER) :
				go1->type = GameObject::GO_EXIT;
				go1->scale.Set(20.f, 15.f, 20.f);
				break;

			case(GameObject::GO_RESTARTHOVER) :
				go1->type = GameObject::GO_RESTART;
				go1->scale.Set(20.f, 15.f, 20.f);
				break;
			}
		}
	}
}

void Buttons::MouseHover(GameObject* hover)
{
	switch (hover->type)
	{
	case(GameObject::GO_PLAY) :
		hover->type = GameObject::GO_PLAYHOVER;
		hover->scale.Set(22.f, 17.f, 22.f);
		break;

	case(GameObject::GO_MENU) :
		hover->type = GameObject::GO_MENUHOVER;
		hover->scale.Set(22.f, 17.f, 22.f);
		break;

	case(GameObject::GO_EDIT) :
		hover->type = GameObject::GO_EDITHOVER;
		hover->scale.Set(22.f, 17.f, 22.f);
		break;

	case(GameObject::GO_LOAD) :
		hover->type = GameObject::GO_LOADHOVER;
		hover->scale.Set(22.f, 17.f, 22.f);
		break;

	case(GameObject::GO_HIGHSCORE) :
		hover->type = GameObject::GO_HIGHSCOREHOVER;
		hover->scale.Set(22.f, 17.f, 22.f);
		break;

	case(GameObject::GO_SAVE) :
		hover->type = GameObject::GO_SAVEHOVER;
		hover->scale.Set(22.f, 17.f, 22.f);
		break;

	case(GameObject::GO_EXIT) :
		hover->type = GameObject::GO_EXITHOVER;
		hover->scale.Set(22.f, 17.f, 22.f);
		break;

	case(GameObject::GO_RESTART) :
		hover->type = GameObject::GO_RESTARTHOVER;
		hover->scale.Set(22.f, 17.f, 22.f);
		break;
	}
}
