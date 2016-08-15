#pragma once

#ifdef MOB_AI_EXPORTS
#define MOB_AI_API __declspec(dllexport) 
#else
#define MOB_AI_API __declspec(dllimport) 
#endif

#include "Vector3.h"

namespace Mob_AI
{

    class MOB_AI_API Mob
    {
    public:
        Mob(float reactionDistance);
        ~Mob();
        
        enum State
        {
            Spawn,
            Idle,
            Attack,
            Die,
        };

        State state;
        float ReactDist;
        Vector3 Position;


        void Init();
        void update();
    };
}