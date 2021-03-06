#pragma once

#ifndef _D3DCLASS_H_
#define _D3DCLASS_H_

// LINKING

#pragma comment(lib, "d3d11.lib")	//Direct3D functionality

#pragma comment(lib, "dxgi.lib")	// Tools to interface with the hardver
//to obtain info about the refresh rate, etc

#pragma comment(lib, "d3dcompiler.lib")	//Functionality for compiling shaders


// INCLUDES
#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;


class D3DClass
{
public:
	D3DClass();
	D3DClass(const D3DClass&);
	~D3DClass();

	bool Initialize(int, int, bool, HWND, bool, float, float);
	void CreateRenderTarget();
	void CleanupRenderTarget();
	void Shutdown();

	void BeginScene(float, float, float, float);
	void SetBackBufferRenderTarget();

	void PresentScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(XMMATRIX&);
	void GetWorldMatrix(XMMATRIX&);
	void GetOrthoMatrix(XMMATRIX&);

	void GetVideoCardInfo(char*, int&);

	void TurnZBufferOn();
	void TurnZBufferOff();

	void TurnOnAlphaBlending();
	void TurnOffAlphaBlending();

	void EnableWireframe();
	void DisableWireframe();

	void LoadTexture(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);


	IDXGISwapChain* GetSwapChain();

	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];

private:
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
public:
	ID3D11RenderTargetView* m_renderTargetView;
private:
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
public:
	ID3D11DepthStencilView* m_depthStencilView;
private:
	ID3D11RasterizerState* m_rasterState;
	ID3D11RasterizerState* m_rasterStateWireframe;
	D3D11_VIEWPORT* m_viewport;



	XMMATRIX m_projectionMatrix;
	XMMATRIX m_worldMatrix;
	XMMATRIX m_orthoMatrix;

	//2D stencil
	ID3D11DepthStencilState* m_depthDisabledStencilState;


	//alpha transparency
	ID3D11BlendState* m_alphaEnableBlendingState;
	ID3D11BlendState* m_alphaDisableBlendingState;

};

#endif // ! _D3DCLASS_H_
