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
	TerrainClass*		m_Terrain;
	ArrowsClass*		m_Arrows;
	RenderTextureClass* m_RenderTexture;

	D3DClass* m_DirectXManager;

};

#endif // !_SCENERENDERERCLASS_H_
