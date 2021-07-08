#ifndef _SCENERENDERERCLASS_H_
#define _SCENERENDERERCLASS_H_

#include "d3dclass.h"
#include "shadermanagerclass.h"
#include "cameraclass.h"
#include "positionclass.h"
#include "terrainclass.h"
#include "arrowsclass.h"
#include "lightclass.h"
#include "modelclass.h"
#include "rendertextureclass.h"
//#include "bitmapclass.h"

// Materials
#include "PBRShaderMaterial.h"
#include "ColorShaderMaterial.h"

#include "SceneLoader.h"

#include <vector>
#include <string>

// mouse inputs
#define MOUSE_LEFT_CLICK    0
#define MOUSE_RIGHT_CLICK   1
#define MOUSE_SCROLL_CLICK  2
#define MOUSE_POS_X         3
#define MOUSE_POS_Y         4


class SceneRenderClass
{
public:
	SceneRenderClass(D3DClass*, HWND);
	~SceneRenderClass();


	bool RenderScene(D3DClass*, int*);
	const char* MessageForConsole;


	ID3D11ShaderResourceView* GetTexture();


	bool LoadObject(const char*);


	void SaveScene();

private:
	PositionClass*		m_Position;
	ShaderManagerClass* m_ShaderManager;
	TerrainClass*		m_Terrain;
	ArrowsClass*		m_Arrows;
	RenderTextureClass* m_RenderTexture;

	int					m_pastMouseX;
	int					m_pastMouseY;

	D3DClass* m_DirectX;
	SceneLoader* m_SceneLoader;

public:
	CameraClass*		m_Camera;

	LightClass*			m_Light;
	

	vector<ModelClass*> m_Models;

	vector<PBRShaderMaterial*> m_PbrMaterials;

	vector<ColorShaderMaterial*> m_ColorMaterials;

};

#endif // !_SCENERENDERERCLASS_H_
