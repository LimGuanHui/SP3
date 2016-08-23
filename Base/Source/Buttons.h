#ifndef BUTTONS_H
#define BUTTONS_H
#include <vector>
#include <Vector3.h>
#include "GameObject.h"
#include "Camera.h"

using std::vector;

class Buttons
{
public:
	Buttons();
	~Buttons();

	void Init(vector<GameObject *> *buttonList);
	void Update(Vector3 mousepos, float dt, vector<GameObject *> *buttonList);
	void MouseHover(GameObject* hover);
	
	bool isClick;
	bool isHover;
	bool isStart, isMenu, isEdit, isLoad, isHighscore, isSave, isExit, isRestart;

	GameObject* button;
	GameObject* PlayButton;
	GameObject* MenuButton;
	GameObject* EditButton;
	GameObject* LoadButton;
	GameObject* HighscoreButton;
	GameObject* SaveButton;
	GameObject* ExitButton;
	GameObject* RestartButton;

	Camera camera;
private:

};

#endif