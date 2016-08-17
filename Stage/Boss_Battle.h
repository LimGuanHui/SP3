#pragma once

#ifndef BOSS_BATTLE_EXPORTS
#define BOSS_BATTLE_API __declspec(dllexport) 
#else
#define BOSS_BATTLE_API __declspec(dllimport) 
#endif

#include "Panel.h"
#include <vector>


class BOSS_BATTLE_API Boss_Battle
    {
    public:
        enum BattleState
        {
            Start,
            Battle,
            End,
        };

        Boss_Battle();
        ~Boss_Battle();
        void Init(Vector3 PanelStartpos);
        void update();
        void exit();

        BattleState battle_state;

        std::vector<Panels::Panel *> P_Panel_List;
        std::vector<Panels::Panel *> E_Panel_List;
    private:
    };


BOSS_BATTLE_API Boss_Battle* CreateBossBattleInstance();