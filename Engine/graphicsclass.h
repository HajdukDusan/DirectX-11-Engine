#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"

#include "lightshaderclass.h"
#include "textureshaderclass.h"
#include "lightclass.h"
#include "spriteclass.h"
#include "modellistclass.h"
#include "frustumclass.h"
#include "Terrainclass.h"
#include "colorshaderclass.h"
#include "arrowsclass.h"
#include "bitmapclass.h"

#include "fontshaderclass.h"
#include "textclass.h"

#include "clipplaneshaderclass.h"



#include <wchar.h>
#include <string>
#include <vector>


#include <SimpleMath.h>

#include <SpriteFont.h>

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = false;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(bool, int, int, float, float, float, float, float);

	CameraClass* GetCamera();

	bool Render(int, int, float, int, int, HWND);

	void TestIntersection(int, int);
	bool RaySphereIntersect(XMFLOAT3, XMFLOAT3, float);

private:
	D3DClass* m_Direct3D;

	CameraClass* m_Camera;


	ModelClass *m_Model;

	ModelClass* m_Model2; 

	LightShaderClass* m_LightShader;
	TextureShaderClass* m_TextureShader;
	ColorShaderClass* m_ColorShader;
	LightClass* m_Light;

	SpriteClass* m_Sprite;

	ModelListClass* m_ModelList;
	FrustumClass* m_Frustum;

	TerrainClass* m_Terrain;

	ArrowsClass* m_Arrows;

	ClipPlaneShaderClass* m_ClipPlaneShader;


	// for drawing the cursor
	BitmapClass* m_Bitmap;

	bool m_beginCheck;
	int m_screenWidth, m_screenHeight;

	string m_ClickedInfo;


	//SimpleMath::Vector2 m_fontPos;
	//unique_ptr<SpriteBatch> spriteBatch;
	//unique_ptr<SpriteFont> spriteFont;

	FontShaderClass* m_FontShader;
	TextClass* m_Text;
};

#endif