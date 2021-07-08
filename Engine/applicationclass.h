#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_


const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = false;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


#include "inputclass.h"
#include "d3dclass.h"
#include "shadermanagerclass.h"
#include "timerclass.h"
#include "fpsclass.h"
#include "zoneclass.h"



class ApplicationClass
{
public:
	ApplicationClass();
	ApplicationClass(const ApplicationClass&);
	~ApplicationClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

private:
	InputClass* m_Input;
	D3DClass* m_Direct3D;
	ShaderManagerClass* m_ShaderManager;
	TimerClass* m_Timer;
	FpsClass* m_Fps;

public:
	ZoneClass* m_Zone;

};

#endif