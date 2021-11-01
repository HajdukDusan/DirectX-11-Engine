#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <directxmath.h>

using namespace DirectX;

class Transform
{
public:
	XMFLOAT3 translation;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;

	Transform(XMFLOAT3 _translation, XMFLOAT3 _rotation, XMFLOAT3 _scale) {
		translation = _translation;
		rotation = _rotation;
		scale = _scale;
	};
	Transform() {
		translation = XMFLOAT3(0, 0, 0);
		rotation = XMFLOAT3(0, 0, 0);
		scale = XMFLOAT3(1, 1, 1);
	};
};

#endif
