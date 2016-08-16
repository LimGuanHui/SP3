#include "Map_Editor.h"
#include <WinUser.h>

Map_Editor::Map_Editor()
{
}


Map_Editor::~Map_Editor()
{
}

void Map_Editor::Init()
{
    edit_state = START;
    mousepos = Vector3(0, 0, 0);
}
void Map_Editor::Update(float dt, Vector3 mousepos)
{
    switch (edit_state)
    {
    case Map_Editor::START:
        if (Map_Editor::IsKeyPressed('1'))
            edit_state = CREATE;
        break;
    case Map_Editor::SAVE:

        break;
    case Map_Editor::LOAD:

        break;
    case Map_Editor::CREATE:

        break;
    case Map_Editor::DESTROY:

        break;
    case Map_Editor::END:

        break;
    default:
        break;
    }
}
Platform* Map_Editor::CreateNewPlatform(Vector3 pos, Vector3 scale, Platform::PLATFORM_TYPE type)
{

    return new Platform(pos,scale,type);
}

bool Map_Editor::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

std::string Map_Editor::getState()
{
    switch (edit_state)
    {   
    case Map_Editor::START:
        return "START";
        break;
    case Map_Editor::SAVE:
        return "SAVE";
        break;
    case Map_Editor::LOAD:
        return "LOAD";
        break;
    case Map_Editor::CREATE:
        return "CREATE";
        break;
    case Map_Editor::DESTROY:
        return "DESTROY";
        break;
    case Map_Editor::END:
        return "END";
        break;
    default:
        break;
    }
}

void Map_Editor::PlatformHandler(Platform* selected_platform , float dt)
{
    unsigned short key = ((GetAsyncKeyState(key) & 0x8001) != 0);

    Vector3 platformpos = selected_platform->getpos();

    switch (key)
    {
    case VK_UP:
        selected_platform->Setpos(Vector3(platformpos.x, platformpos.y + dt * 5.f, 0));
        break;
    case VK_DOWN:
        selected_platform->Setpos(Vector3(platformpos.x, platformpos.y - dt * 5.f, 0));
        break;
    case VK_LEFT:
        selected_platform->Setpos(Vector3(platformpos.x - dt * 5.f, platformpos.y, 0));
        break;
    case VK_RIGHT:
        selected_platform->Setpos(Vector3(platformpos.x + dt * 5.f, platformpos.y, 0));
        break;

    default:
        break;
    }
}