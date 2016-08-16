#pragma once

#ifndef PANEL_EXPORTS
#define PANEL_API __declspec(dllexport) 
#else
#define PANEL_API __declspec(dllimport) 
#endif

//#include "Vector3.h"

namespace Panels
{
    class PANEL_API Panel
    {
    public:
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

        enum PanelState
        {
            Empty,
            Occupied,
            HasDMG,
            Occupied_and_HasDMG,
        };

        Panel();
        ~Panel();
        void Init(int panelNo, /*Vector3 startpos,*/ float offset, PanelType panel_type);
        void update(int *playerhp);

        PanelPos panel_pos;
        PanelType panel_type;
        PanelState panel_state;
    private:
        //Vector3 Pos;
        int PanelNo;
        float offset;
        
    };

}

