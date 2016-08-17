
#include "Boss_Battle.h"

Boss_Battle::Boss_Battle()
{
}

Boss_Battle::~Boss_Battle()
{
}

void Boss_Battle::Init(Vector3 PanelStartpos)
{
    battle_state = Start;
    for (int i = 0; i < 9; i++)
    {
        Panels::Panel *N_panel = new Panels::Panel();
        N_panel->Init(i, PanelStartpos, 15.0f, Panels::Panel::Normal);
        P_Panel_List.push_back(N_panel);
    }
}
void Boss_Battle::update()
{
    switch (battle_state)
    {
    case Boss_Battle::Start:
        break;
    case Boss_Battle::Battle:
        break;
    case Boss_Battle::End:
        break;
    default:
        break;
    }
}

void Boss_Battle::exit()
{
    if (P_Panel_List.size() > 0)
        P_Panel_List.clear();
    if (E_Panel_List.size() > 0)
        E_Panel_List.clear();
}


Boss_Battle* CreateBossBattleInstance()
{
    return new Boss_Battle();
}