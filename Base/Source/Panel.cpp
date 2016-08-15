#include "Panel.h"


Panel::Panel()
{
}


Panel::~Panel()
{
}

void Panel::Init(int panelNo, Vector3 startpos, float offset)
{
    this->offset = offset;
    switch (panelNo)    
    {
    case 0:
        Pos = startpos;
        PanelNo = panelNo;
        break;
    case 1:
        Pos = Vector3(startpos.x,startpos.y + offset,startpos.z);
        PanelNo = panelNo;
        break;
    case 2:
        Pos = Vector3(startpos.x, startpos.y + offset * 2, startpos.z);
        PanelNo = panelNo;
        break;
    case 3:
        Pos = Vector3(startpos.x + offset, startpos.y, startpos.z);
        PanelNo = panelNo;
        break;
    case 4:
        Pos = Vector3(startpos.x + offset, startpos.y + offset, startpos.z);
        PanelNo = panelNo;
        break;
    case 5:
        Pos = Vector3(startpos.x + offset, startpos.y + offset * 2, startpos.z);
        PanelNo = panelNo;
        break;
    case 6:
        Pos = Vector3(startpos.x + offset * 2, startpos.y, startpos.z);
        PanelNo = panelNo;
        break;
    case 7:
        Pos = Vector3(startpos.x + offset * 2, startpos.y + offset, startpos.z);
        PanelNo = panelNo;
        break;
    case 8:
        Pos = Vector3(startpos.x + offset * 2, startpos.y + offset * 2, startpos.z);
        PanelNo = panelNo;
        break;
    default:
        break;
    }
}

void Panel::update(int *playerhp)
{

}
