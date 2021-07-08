#ifndef _ZONECLASS_H_
#define _ZONECLASS_H_


#include "d3dclass.h"
#include "inputclass.h"
#include "shadermanagerclass.h"
#include "timerclass.h"
#include "userinterfaceclass.h"
#include "cameraclass.h"
#include "positionclass.h"
#include "terrainclass.h"
#include "arrowsclass.h"

#include "lightclass.h"
#include "modelclass.h"

#include "rendertextureclass.h"

#include "bitmapclass.h"

#include "PBRshaderclass.h"

#include "guiclass.h"


#include <string>

class ZoneClass
{
public:
	ZoneClass();
	ZoneClass(const ZoneClass&);
	~ZoneClass();

	bool Initialize(D3DClass*, HWND, int, int, float);
	void Shutdown();
	bool Frame(D3DClass*, InputClass*, ShaderManagerClass*, float, int);

private:
	void HandleMovementInput(InputClass*, float);
	bool Render(D3DClass*, ShaderManagerClass*, int, int, float);

	void RenderImGui();

private:
	UserInterfaceClass* m_UserInterface;
	CameraClass* m_Camera;
	PositionClass* m_Position;
	TerrainClass* m_Terrain;
	ArrowsClass* m_Arrows;
	BitmapClass* m_Circle;
	LightClass* m_Light;
	ModelClass* m_Model;
	BitmapClass* m_MousePointer;


	ModelClass* m_SmoothModel;

	PBRShaderClass* m_NormalMapShader;

	int m_PreviousMouseX;
	int m_PreviousMouseY;

	bool m_displayUI;

	// shader data
	float m_NormalStrength;

public:
	GuiClass* m_GUI;

	RenderTextureClass* m_RenderTexture;

};

#endif