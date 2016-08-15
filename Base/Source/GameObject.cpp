
#include "GameObject.h"

GameObject::GameObject(GAMEOBJECT_TYPE typeValue)
: type(typeValue),
scale(1, 1, 1),
active(false),
mass(1.f),
normal(0, 0, 0),
name("nameless"),
up(false),
moveSpeed(0),
moveTime(0),
moveDebouncetimer(0),
connect(NULL),
hp(0),
interpolation(0),
fireTimer(0),
DeflectorNo(0)
{
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
    type = GameObject::GO_BALL;
    scale = Vector3(1, 1, 1);
    active = false;
    mass = 1.f;
    normal = Vector3(0, 0, 0);
    name = string("nameless");
    up = false;
    moveSpeed = 0;
    moveTime = 0;
    moveDebouncetimer = 0;
    connect = NULL;
    hp = 0;
    interpolation = 0;
    fireTimer = 0;
    DeflectorNo = 0;
}
