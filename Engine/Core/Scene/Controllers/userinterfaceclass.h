#ifndef _USERINTERFACECLASS_H_
#define _USERINTERFACECLASS_H_

#include "../../Renderer/Shaders/Font/textclass.h"
#include "../../Renderer/DirectX/d3dclass.h"

class UserInterfaceClass
{
public:
	UserInterfaceClass();
	UserInterfaceClass(const UserInterfaceClass&);
	~UserInterfaceClass();

	bool Initialize(D3DClass*, int, int);
	void Shutdown();

	bool Frame(ID3D11DeviceContext*, int, float, float, float, float, float, float);
	bool Render(D3DClass*, XMMATRIX, XMMATRIX, XMMATRIX);

private:
	bool UpdateFpsString(ID3D11DeviceContext*, int);
	bool UpdatePositionStrings(ID3D11DeviceContext*, float, float, float, float, float, float);

private:
	FontClass* m_Font1;
	TextClass* m_FpsString, * m_VideoStrings, * m_PositionStrings;
	int m_previousFps;
	int m_previousPosition[6];
};

#endif