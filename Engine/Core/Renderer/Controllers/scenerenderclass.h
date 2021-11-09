#ifndef _SCENERENDERERCLASS_H_
#define _SCENERENDERERCLASS_H_

#include "../Utils/rendertextureclass.h"

#include <vector>
#include <string>
#include "../../Scene/Controllers/GameManager.h"


class SceneRenderClass
{
public:
	SceneRenderClass(D3DClass*, HWND);
	~SceneRenderClass();


	bool RenderScene(GameManager* GameManager, Camera* Camera, RenderTextureClass* RenderTexture);


	bool LoadObject(const char*);


	void SaveScene();

private:
	RenderTextureClass* m_RenderTexture;

	D3DClass* m_DirectXManager;

};

#endif // !_SCENERENDERERCLASS_H_
