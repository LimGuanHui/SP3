#pragma once

#ifndef MAP_EDITOR_EXPORTS
#define MAP_EDITOR_API __declspec(dllexport) 
#else
#define MAP_EDITOR_API __declspec(dllimport) 
#endif

#include "Platform.h"
#include <vector>
#include <string>

class MAP_EDITOR_API Map_Editor
{
public:
    Map_Editor();
    ~Map_Editor();

    enum EDIT_STATE
    {
        START,
        SAVE,
        LOAD,
        CREATE,
        DESTROY,
        END,
    };

    EDIT_STATE edit_state;

    void Init();
    void Update(float dt, Vector3 mousepos);
    void PlatformHandler(Platform* selected_platform, float dt);
    std::string getState();
    static bool IsKeyPressed(unsigned short key);
    Platform* CreateNewPlatform(Vector3 pos, Vector3 scale, Platform::PLATFORM_TYPE type);

    std::vector<Platform* > Platform_List;
private:
    Vector3 mousepos;
};

