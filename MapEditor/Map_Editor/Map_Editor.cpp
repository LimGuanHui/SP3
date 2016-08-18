#include "Map_Editor.h"
#include <iostream>
#include <Windows.h>

#define inputTimer 0.3f

Map_Editor::Map_Editor()
{
}


Map_Editor::~Map_Editor()
{
}

void Map_Editor::Init(Vector3 topofScreen)
{
    edit_state = CREATE;
    mousepos = Vector3(0, 0, 0);
    curr = NULL;
    nullplat = CreateNewPlatform(Vector3(0, 0, 0), Vector3(0, 0, 0), Platform::End_of_Type);
    inputDelayTimer = inputTimer;
    DisplayAvailablePlatforms(topofScreen);
}
void Map_Editor::Update(float dt, Vector3 mousepos)
{
    if (curr == NULL)
    {
        curr = nullplat;
    }
    if (inputDelayTimer > 0)
    {
        inputDelayTimer -= dt;
    }
    this->mousepos = mousepos;
    switch (edit_state)
    {
    case Map_Editor::START:
        if (Map_Editor::IsKeyPressed('1') && inputDelayTimer <= 0)
        {
            inputDelayTimer = inputTimer;
            edit_state = CREATE;
        }
        
        break;
    case Map_Editor::SAVE:

        break;
    case Map_Editor::LOAD:

        break;
    case Map_Editor::CREATE:
        if (Map_Editor::IsKeyPressed('2') && inputDelayTimer <= 0)
        {
            inputDelayTimer = inputTimer;
            curr = CreateNewPlatform(mousepos, Vector3(1, 1, 1), Platform::Normal);
            edit_state = MANAGE;
        }
        else if ((GetKeyState(VK_RBUTTON) & 0x100) != 0 && inputDelayTimer <= 0)
        {
            inputDelayTimer = inputTimer;
            MouseOverCreatePlatform();
            edit_state = MANAGE;
        }
        break;
    case Map_Editor::MANAGE:
        if (IsKeyPressed(VK_ESCAPE))
            edit_state = END;
        else if (IsKeyPressed('1') && inputDelayTimer <= 0)
        {
            inputDelayTimer = inputTimer;
            edit_state = CREATE;
        }
            
        else if (IsKeyPressed(' ') && inputDelayTimer <= 0)
        {
            inputDelayTimer = inputTimer;
            curr = CreateNewPlatform(curr->getpos(), curr->getscale(), curr->type);
        }
        else if ((GetKeyState(VK_RBUTTON) & 0x100) != 0 && inputDelayTimer <= 0)
        {
            inputDelayTimer = inputTimer;
            MouseOverCreatePlatform();
        }
        else if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && IsKeyPressed(VK_SHIFT) && inputDelayTimer <= 0)
        {
            inputDelayTimer = inputTimer;
            MouseOverSelectPlatform();
        }
        else if (IsKeyPressed(VK_DELETE) && curr != nullplat && inputDelayTimer <= 0)
        {
            inputDelayTimer = inputTimer;
            DeleteSelected();
        }
        PlatformHandler(curr, dt);
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
    Platform* Newplatform = new Platform(pos, scale, type);
    Platform_List.push_back(Newplatform);
    return Newplatform;
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
    Vector3 platform;


    platform = selected_platform->getscale();


    if (IsKeyPressed(VK_UP) && IsKeyPressed(VK_SHIFT))
    {
        selected_platform->Setscale(Vector3(platform.x, platform.y + dt * 5.f, platform.z));
        return;
    }
    else if (IsKeyPressed(VK_DOWN) && IsKeyPressed(VK_SHIFT))
    {
        selected_platform->Setscale(Vector3(platform.x, platform.y - dt * 5.f, platform.z));
        return;
    }
     if (IsKeyPressed(VK_LEFT) && IsKeyPressed(VK_SHIFT))
    {
        selected_platform->Setscale(Vector3(platform.x - dt * 5.f, platform.y, platform.z));
        return;
    }
    else if (IsKeyPressed(VK_RIGHT) && IsKeyPressed(VK_SHIFT))
    {
        selected_platform->Setscale(Vector3(platform.x + dt * 5.f, platform.y, platform.z));
        return;
    }

    platform = selected_platform->getpos();

    if (IsKeyPressed(VK_UP))
    {
        selected_platform->Setpos(Vector3(platform.x, platform.y + dt * 35.f, platform.z));
        
    }
    else if (IsKeyPressed(VK_DOWN))
    {
        selected_platform->Setpos(Vector3(platform.x, platform.y - dt * 35.f, platform.z));
        
    }
    if (IsKeyPressed(VK_LEFT))
    {
        selected_platform->Setpos(Vector3(platform.x - dt * 35.f, platform.y, platform.z));
        
    }
    else if (IsKeyPressed(VK_RIGHT))
    {
        selected_platform->Setpos(Vector3(platform.x + dt * 35.f, platform.y, platform.z));
        
    }

    if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
    {
        selected_platform->Setpos(Vector3(mousepos.x, mousepos.y, mousepos.z));
    }



}

std::string Map_Editor::TextForDisplay()
{
    switch (edit_state) 
    {
    case Map_Editor::START:
        return "Start Mode: (1)go to creation";
        break;
    case Map_Editor::SAVE:
        break;
    case Map_Editor::LOAD:
        break;
    case Map_Editor::CREATE:
        return "Create Mode:(2)create basic platform";
        break;
    case Map_Editor::MANAGE:
        return "ManageMode:(ESC) to gtfo,(1)to go create again, arrow keys to move the platform, hold shift for scale";
        break;
    case Map_Editor::DESTROY:
        break;
    case Map_Editor::END:
        return "Go to game?";
        break;
    default:
        break;
    }
}

void Map_Editor::DisplayAvailablePlatforms(Vector3 topofScreen)
{
    Platform_Display_List.clear();
    for (int i = 0; i<Platform::End_of_Type; i++)
    {
        Platform::PLATFORM_TYPE platType = (Platform::PLATFORM_TYPE)i;
        Vector3 displaypos = Vector3(topofScreen.x + (i * 10), topofScreen.y,topofScreen.z);
        Platform* NEW_display_platform = new Platform(displaypos, Vector3(20, 20, 20), platType);
        Platform_Display_List.push_back(NEW_display_platform);
    }
    //example
    /*enum enumType
    {
        A = 0,
        B,
        C,
        enumTypeEnd
    };

    for (int i = 0; i<enumTypeEnd; i++)
    {
        enumType eCurrent = (enumType)i;
    }
*/
}

std::string Map_Editor::getfilename(std::string fileDir)
{
    return "";
}

void Map_Editor::MouseOverCreatePlatform()
{
    for (std::vector<Platform *>::iterator it = Platform_Display_List.begin(); it != Platform_Display_List.end(); ++it)
    {
        Platform *go1 = (Platform *)*it;
        float distanceSquared = ((go1->getpos()) - (mousepos)).LengthSquared();
        float combinedRadiusSquared = (go1->getscale().x - 8.f) * (go1->getscale().x - 8.f);
        Vector3 relativeDisplacement = mousepos - go1->getpos();
        if (distanceSquared < combinedRadiusSquared)
        {
            curr = CreateNewPlatform(mousepos, go1->getscale(), go1->type);
            return;
        }
    }
}

void Map_Editor::MouseOverSelectPlatform()
{
    for (std::vector<Platform *>::iterator it = Platform_List.begin(); it != Platform_List.end(); ++it)
    {
        Platform *go1 = (Platform *)*it;
        float distanceSquared = ((go1->getpos()) - (mousepos)).LengthSquared();
        float combinedRadiusSquared = (go1->getscale().x - 8.f) * (go1->getscale().x - 8.f);
        Vector3 relativeDisplacement = mousepos - go1->getpos();
        if (distanceSquared < combinedRadiusSquared)
        {
            curr = go1;
            return;
        }
    }
}

void Map_Editor::DeleteSelected()
{
    for (std::vector<Platform *>::iterator it = Platform_List.begin(); it != Platform_List.end(); ++it)
    {
        Platform *p = (Platform *)*it;
        if (curr == p)
        {
            Platform_List.erase(it);
            curr = nullplat;
            return;
        }
    }
}

Map_Editor* CreateNewMapEditorInstance()
{
    return new Map_Editor();
}

