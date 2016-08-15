#pragma once

#ifdef MOB_AI_EXPORTS
#define MOB_AI_API __declspec(dllexport) 
#else
#define MOB_AI_API __declspec(dllimport) 
#endif



namespace MOB_AI
{

    class Mob
    {
    public:
        MOB_AI_API Mob(float reactionDistance);
        MOB_AI_API ~Mob();
        
        enum State
        {
            Spawn,
            Idle,
            Attack,
            Die,
        };

        State state;
        float ReactDist;
        
        

        MOB_AI_API void Init();
        MOB_AI_API void update();
    };
}