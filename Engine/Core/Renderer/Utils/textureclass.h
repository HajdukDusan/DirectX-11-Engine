#ifndef _TEXTURECLASS_H_
#define _TEXTURECLASS_H_


#include <d3d11.h>
#include <stdio.h>

#include "WICTextureLoader.h";
#include <wrl.h>

using namespace DirectX;
using namespace Microsoft::WRL;

class TextureClass
{
private:
	struct TargaHeader
	{
		unsigned char data1[12];
		unsigned short width;
		unsigned short height;
		unsigned char bpp;
		unsigned char data2;
	};

public:
	TextureClass();
	TextureClass(const TextureClass&);
	~TextureClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, const char*);

	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();

private:
	bool LoadTarga(const char*, int&, int&);

private:
	unsigned char* m_targaData;
	//ID3D11Resource
	ID3D11Texture2D* m_texture;
	ID3D11ShaderResourceView* m_textureView;

};

HRESULT CreateWICTextureFromFile(ID3D11Device* d3dDevice,
	ID3D11DeviceContext* d3dContext,
	const wchar_t* szFileName,
	ID3D11Resource** texture, ID3D11ShaderResourceView** textureView,
	size_t maxsize = 0);

#endif