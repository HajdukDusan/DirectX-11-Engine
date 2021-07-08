#ifndef _TEXTUREARRAYCLASS_H_
#define _TEXTUREARRAYCLASS_H_

#include <d3d11.h>
#include <stdio.h>
//#include <d3dx11tex.h>


class TextureArrayClass
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
	TextureArrayClass();
	TextureArrayClass(const TextureArrayClass&);
	~TextureArrayClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, const char*, const char*, const char*);
	void Shutdown();

	bool LoadTargaInShaderResourceView(ID3D11Device*, ID3D11DeviceContext*, const char*, int);

	ID3D11ShaderResourceView** GetTextureArray();

private:

	unsigned char* m_targaData;
	ID3D11Texture2D* m_texture;

	ID3D11ShaderResourceView* m_textures[3];
};

#endif