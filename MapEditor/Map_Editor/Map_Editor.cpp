#include "Map_Editor.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <io.h>
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
    nullplat = CreatePlatform(Vector3(0, 0, 0), Vector3(0, 0, 0), Platform::End_of_Type);
    inputDelayTimer = inputTimer;
    DisplayAvailablePlatforms(topofScreen);
    Fileselect = "";
    pushedfilenames = false;
}
void Map_Editor::Update(float dt, Vector3 mousepos)
{
    if (edit_state != SAVE)
        Fileselect = "";
    if (curr == NULL)
        curr = nullplat;
    if (inputDelayTimer > 0)
        inputDelayTimer -= dt;
    this->mousepos = mousepos;
    if (edit_state != SAVE || edit_state != LOAD)
        pushedfilenames = false;
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
        if (!pushedfilenames)
            PushFilenamesIntoStringVec();
        FileSelection();
        if (IsKeyPressed(VK_RETURN))
        {
            SaveToFile(Fileselect);
            Fileselect = "SAVED";
            edit_state = MANAGE;
        }
        break;
    case Map_Editor::LOAD:
        if (!pushedfilenames)
            PushFilenamesIntoStringVec();
        FileSelection(); 
        if (IsKeyPressed(VK_RETURN))
        {
            LoadFromFile(Fileselect);
            Fileselect = "LOADED";
            edit_state = MANAGE;
        }
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
        else if (IsKeyPressed('S') && inputDelayTimer <= 0)
        {
            inputDelayTimer = inputTimer;
            edit_state = SAVE;
        }
        else if (IsKeyPressed('L') && inputDelayTimer <= 0)
        {
            inputDelayTimer = inputTimer;
            edit_state = LOAD;
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

Platform* Map_Editor::CreatePlatform(Vector3 pos, Vector3 scale, Platform::PLATFORM_TYPE type)
{
    Platform* Newplatform = new Platform(pos, scale, type);
    //Platform_List.push_back(Newplatform);
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
        return "Save Mode: up and down arrow keys select file, enter to select";
        break;
    case Map_Editor::LOAD:
        return "Load Mode: up and down arrow keys select file, enter to select";
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
        return "";
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
        Platform* NEW_display_platform = new Platform(displaypos, Vector3(7, 7, 7), platType);
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
            return; // to prevent anymore interation
        }

    }
}

void Map_Editor::PushFilenamesIntoStringVec()
{
    HMODULE hModule = GetModuleHandleW(NULL);
    WCHAR path[MAX_PATH];
    GetModuleFileNameW(hModule, path, MAX_PATH);
    char ch[MAX_PATH];
    char de = ' ';
    WideCharToMultiByte(CP_ACP, 0, path, -1, ch, MAX_PATH, &de, NULL);
    std::string dir = std::string(ch);
    std::string actual_dir = dir.substr(0, dir.find("Deb"));
    actual_dir += "Maps\\*.txt";
    _finddata_t data;
    std::string filename;
    SaveList.clear();

    int check = _findfirst(actual_dir.c_str(), &data);
    if (check != -1)
    {
        int check2 = 0;
        while (check2 != -1)
        {
            filename = data.name;
            SaveList.push_back(filename);
            check2 = _findnext(check, &data);
        }
        _findfirst(actual_dir.c_str(), &data);
        Fileselect = data.name;
        _findclose(check);
    }
    pushedfilenames = true;
    
}

void Map_Editor::FileSelection()
{
    if (IsKeyPressed(VK_UP) && inputDelayTimer <= 0)
    {
        inputDelayTimer = inputTimer;
        for (std::vector<std::string>::iterator it = SaveList.begin(); it != SaveList.end(); ++it)
        {
            std::string p = (std::string )*it;
            if (Fileselect == p)
            {
                if (it != SaveList.begin())
                    Fileselect = (std::string)*--it;
                else
                {
                    std::vector<std::string>::iterator it2 = SaveList.end();
                    --it2;
                    Fileselect = (std::string)*it2;
                    return;
                }
                    
            }
        }
    }
    if (IsKeyPressed(VK_DOWN) && inputDelayTimer <= 0)
    {
        inputDelayTimer = inputTimer;
        for (std::vector<std::string>::iterator it = SaveList.begin(); it != SaveList.end(); ++it)
        {
            std::string p = (std::string)*it;
            if (Fileselect == p)
            {
                std::vector<std::string>::iterator it2 = SaveList.end();
                --it2;
                if (it != it2)
                    Fileselect = (std::string)* ++it;
                else
                {
                    Fileselect = (std::string)* SaveList.begin();
                    return;
                }
                    
            }
        }
    }
}

void Map_Editor::SaveToFile(std::string Nfile)
{
    HMODULE hModule = GetModuleHandleW(NULL);
    WCHAR path[MAX_PATH];
    GetModuleFileNameW(hModule, path, MAX_PATH);
    char ch[MAX_PATH];
    char de = ' ';
    WideCharToMultiByte(CP_ACP, 0, path, -1, ch, MAX_PATH, &de, NULL);
    std::string dir = std::string(ch);
    std::string actual_dir = dir.substr(0, dir.find("Deb"));
    actual_dir += "Maps\\";
    actual_dir += Nfile;

    std::ofstream file(actual_dir.c_str());
    if (file.is_open())
    {
        bool written = false;
        while (file.good() && !written)
        {
            for (std::vector<Platform* >::iterator it = Platform_List.begin(); it != Platform_List.end(); ++it)
            {
                Platform* go = (Platform*)*it;
                std::vector<Platform* >::iterator it2 = Platform_List.end();
                --it2;
                if (it == it2)
                {
                    file << "type:" << go->type << "," << "pos:x:" << go->getpos().x << ",y:" << go->getpos().y << ",z:" << go->getpos().z << ","
                        << "scale:x:" << go->getscale().x << ",y:" << go->getscale().y << ",z:" << go->getscale().z;

                    written = true;
                }
                else
                {
                    file << "type:" << go->type << "," << "pos:x:" << go->getpos().x << ",y:" << go->getpos().y << ",z:" << go->getpos().z << ","
                        << "scale:x:" << go->getscale().x << ",y:" << go->getscale().y << ",z:" << go->getscale().z << "\n";

                }
            }
        }
    }
    file.close();
}

void Map_Editor::LoadFromFile(std::string Nfile)
{
    HMODULE hModule = GetModuleHandleW(NULL);
    WCHAR path[MAX_PATH];
    GetModuleFileNameW(hModule, path, MAX_PATH);
    char ch[MAX_PATH];
    char de = ' ';
    WideCharToMultiByte(CP_ACP, 0, path, -1, ch, MAX_PATH, &de, NULL);
    std::string dir = std::string(ch);
    std::string actual_dir = dir.substr(0, dir.find("Deb"));
    actual_dir += "Maps\\";
    actual_dir += Nfile;

    Platform_List.clear();

    std::ifstream file(actual_dir.c_str());
    if (file.is_open())
    {
        while (file.good())
        {
            std::string read_data;
            getline(file, read_data,'\n');
            
            std::string plat_type = read_data.substr(read_data.find(":") + 1, 1);
            int l = read_data.find(",s") - read_data.find("pos:") + 3;
            std::string plat_pos = read_data.substr(read_data.find("pos:") + 3, (read_data.find("scale") - 6) - read_data.find("pos:") + 3);
            std::string plat_scale = read_data.substr(read_data.find("scale:") + 5);

            int c_type = stoi(plat_type);
            Vector3 c_pos = Vector3(stof(plat_pos.substr(plat_pos.find("x:") + 2/*, plat_pos.size() - plat_pos.find("y:") - 2*/)),
                stof(plat_pos.substr(plat_pos.find("y:") + 2/*, plat_pos.size() - plat_pos.find("z:") - 2*/))
                , stof(plat_pos.substr(plat_pos.find("z:") + 2/*, plat_pos.size() - plat_pos.find("scale:") - 6*/)));

            Vector3 c_scale = Vector3(stof(plat_scale.substr(plat_scale.find("x:") + 2/*, plat_pos.size() - plat_pos.find("y:") - 2*/)),
                stof(plat_scale.substr(plat_scale.find("y:") + 2/*, plat_pos.size() - plat_pos.find("z:") - 2*/))
                , stof(plat_scale.substr(plat_scale.find("z:") + 2/*, plat_pos.size() - plat_pos.find("scale:") - 6*/)));

            CreateNewPlatform(c_pos, c_scale, static_cast<Platform::PLATFORM_TYPE>(c_type));
        }
    }
    file.close();
}

std::string Map_Editor::getSelectedFile()
{
    return Fileselect;
}

Map_Editor* CreateNewMapEditorInstance()
{
    return new Map_Editor();
}

