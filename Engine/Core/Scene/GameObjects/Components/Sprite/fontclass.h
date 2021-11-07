#ifndef _FONTCLASS_H_
#define _FONTCLASS_H_

#include "../../Core/Renderer/Utils/textureclass.h"

#include <directxmath.h>
#include <fstream>
using namespace DirectX;
using namespace std;


class FontClass
{
private:
	struct FontType
	{
		float left, right;
		int size;
	};

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

public:
	FontClass();
	FontClass(const FontClass&);
	~FontClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, const char*, const char*, float, int);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();
	void BuildVertexArray(void*, const char*, float, float);
	int GetSentencePixelLength(const char*);
	int GetFontHeight();

private:
	bool LoadFontData(const char*);
	void ReleaseFontData();
	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, const char*);
	void ReleaseTexture();

private:
	FontType* m_Font;
	TextureClass* m_Texture;
	float m_fontHeight;
	int m_spaceSize;
};

#endif