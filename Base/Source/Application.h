
#ifndef APPLICATION_H
#define APPLICATION_H

//#include <irrKlang.h>
#include "timer.h"
//using namespace irrklang;

class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	static bool IsMousePressed(unsigned short key);
	static void GetCursorPos(double *xpos, double *ypos);
	static int GetWindowWidth();
	static int GetWindowHeight();

    /*ISoundEngine* theSoundEngine;
    ISoundSource* BGM;*/

private:
	Application();
	~Application();

	//Declare a window object
	StopWatch m_timer;
    double m_dElapsedTime;
    double m_dAccumulatedTime_ThreadOne;
    double m_dAccumulatedTime_ThreadTwo;

};

#endif