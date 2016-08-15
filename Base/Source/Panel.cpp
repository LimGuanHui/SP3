#include "Panel.h"


Panel::Panel()
{
}


Panel::~Panel()
{
}

void Panel::Init(int panelNo, Vector3 startpos)
{
    switch (panelNo)    
    {
    case 0:
        Pos = startpos;
        PanelNo = panelNo;
        break;
    case 1:

        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;
    default:
        break;
    }
}