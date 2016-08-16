#pragma once

#ifndef BOSS_BATTLE_EXPORTS
#define BOSS_BATTLE_API __declspec(dllexport) 
#else
#define BOSS_BATTLE_API __declspec(dllimport) 
#endif

#include "Panel.h"
#include <vector>


    class Boss_Battle
    {
    public:
        enum BattleState
        {
            Start,
            Battle,
            End,
        };

        BOSS_BATTLE_API Boss_Battle();
        BOSS_BATTLE_API ~Boss_Battle();
        void BOSS_BATTLE_API Init();
        void BOSS_BATTLE_API update();
        void  BOSS_BATTLE_API exit();

        BattleState battle_state;

        std::vector<Panels::Panel *> P_Panel_List;
        std::vector<Panels::Panel *> E_Panel_List;
    private:
    };
