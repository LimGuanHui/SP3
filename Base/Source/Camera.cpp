#include "Camera.h"
#include "Application.h"
#include "Mtx44.h"

Camera::Camera()
{
	Reset();
}

Camera::~Camera()
{
}

void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;
    CAM_SPEED = 20;
}

void Camera::Reset()
{
	position.Set(1, 0, 0);
	target.Set(0, 0, 0);
	up.Set(0, 1, 0);
}

void Camera::Update(double dt)
{
    if (Application::IsKeyPressed(VK_UP))
    {
        position.y += dt * CAM_SPEED  ;
        target.y += dt * CAM_SPEED  ;
    }
    if (Application::IsKeyPressed(VK_LEFT))
    {
        position.x -= dt * CAM_SPEED  ;
        target.x -= dt * CAM_SPEED  ;
    }
    if (Application::IsKeyPressed(VK_DOWN))
    {
        position.y -= dt * CAM_SPEED  ;
        target.y -= dt * CAM_SPEED  ;
    }
    if (Application::IsKeyPressed(VK_RIGHT))
    {
        position.x += dt * CAM_SPEED  ;
        target.x += dt * CAM_SPEED  ;
    }
}