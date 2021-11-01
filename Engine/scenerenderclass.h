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
#include "GameManager.h"

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


	bool RenderScene(GameManager* GameManager);


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

	D3DClass* m_DirectXManager;

public:

	//vector<PBRShaderMaterial*> m_PbrMaterials;

	vector<ColorShaderMaterial*> m_ColorMaterials;

};

#endif // !_SCENERENDERERCLASS_H_
