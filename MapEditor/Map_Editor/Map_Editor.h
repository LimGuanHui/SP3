#pragma once

#ifndef MAP_EDITOR_EXPORTS
#define MAP_EDITOR_API __declspec(dllexport) 
#else
#define MAP_EDITOR_API __declspec(dllimport) 
#endif

class MAP_EDITOR_API Map_Editor
{
public:
    Map_Editor();
    ~Map_Editor();
};

