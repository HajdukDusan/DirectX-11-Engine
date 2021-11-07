#ifndef _FRUSTUMCLASS_H_
#define _FRUSTUMCLASS_H_


#define _XM_NO_INTRINSICS_
#include <DirectXMath.h>
using namespace DirectX;

class FrustumClass
{
public:
	FrustumClass();
	FrustumClass(const FrustumClass&);
	~FrustumClass();

	void ConstructFrustum(float, XMMATRIX, XMMATRIX);

	bool CheckPoint(float, float, float);
	bool CheckCube(float, float, float, float);
	bool CheckSphere(float, float, float, float);
	bool CheckRectangle(float, float, float, float, float, float);

private:
	XMVECTOR m_planes[6];
};

#endif