#ifndef PANEL_H
#define PANEL_H

#include "Vector3.h"

class Panel
{
public:
    Panel();
    ~Panel();
    void Init(int panelNo, Vector3 startpos);

    Vector3 Pos;
    int PanelNo;
    float offset;

    enum PanelPos
    {
        Top,
        Middle,
        Bottom,
    };

    enum PanelType
    {
        Normal,
    };

    PanelPos panelpos;
};


#endif