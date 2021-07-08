#include "frustumclass.h"


FrustumClass::FrustumClass()
{
}


FrustumClass::FrustumClass(const FrustumClass& other)
{
}


FrustumClass::~FrustumClass()
{
}


void FrustumClass::ConstructFrustum(float screenDepth, XMMATRIX projectionMatrix, XMMATRIX viewMatrix)
{
	float zMinimum, r;
	XMMATRIX matrix;


	// Calculate the minimum Z distance in the frustum.
	zMinimum = -projectionMatrix._43 / projectionMatrix._33;
	r = screenDepth / (screenDepth - zMinimum);
	projectionMatrix._33 = r;
	projectionMatrix._43 = -r * zMinimum;

	// Create the frustum matrix from the view matrix and updated projection matrix.
	matrix = XMMatrixMultiply(viewMatrix, projectionMatrix);

	// Calculate near plane of frustum.
	m_planes[0] = XMVectorSet(matrix._14 + matrix._13, matrix._24 + matrix._23, matrix._34 + matrix._33, matrix._44 + matrix._43);
	XMVector4Normalize(m_planes[0]);

	// Calculate far plane of frustum.
	m_planes[1] = XMVectorSet(matrix._14 + matrix._13, matrix._24 + matrix._23, matrix._34 + matrix._33, matrix._44 + matrix._43);
	XMVector4Normalize(m_planes[1]);

	// Calculate left plane of frustum.
	m_planes[2] = XMVectorSet(matrix._14 + matrix._11, matrix._24 + matrix._21, matrix._34 + matrix._31, matrix._44 + matrix._41);
	XMVector4Normalize(m_planes[2]);

	// Calculate right plane of frustum.
	m_planes[3] = XMVectorSet(matrix._14 - matrix._11, matrix._24 - matrix._21, matrix._34 - matrix._31, matrix._44 - matrix._41);
	XMVector4Normalize(m_planes[3]);

	// Calculate top plane of frustum.
	m_planes[4] = XMVectorSet(matrix._14 - matrix._12, matrix._24 - matrix._22, matrix._34 - matrix._32, matrix._44 - matrix._42);
	XMVector4Normalize(m_planes[4]);

	// Calculate bottom plane of frustum.
	m_planes[5] = XMVectorSet(matrix._14 + matrix._12, matrix._24 + matrix._22, matrix._34 + matrix._32, matrix._44 + matrix._42);
	XMVector4Normalize(m_planes[5]);

	return;
}

bool FrustumClass::CheckPoint(float x, float y, float z)
{
	int i;

	// Check if the point is inside all six planes of the view frustum.
	for (i = 0; i < 6; i++)
	{
		if (XMVectorGetX(XMPlaneDotCoord(m_planes[i], { x, y, z })) < 0.0f)
		{
			return false;
		}
	}
	return true;
}

bool FrustumClass::CheckCube(float xCenter, float yCenter, float zCenter, float radius)
{
	int i;


	// Check if any one point of the cube is in the view frustum.
	for (i = 0; i < 6; i++)
	{
		if (XMVectorGetX(XMPlaneDotCoord(m_planes[i], { (xCenter - radius), (yCenter - radius), (zCenter - radius) })) >= 0.0f)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(m_planes[i], { (xCenter + radius), (yCenter - radius), (zCenter - radius) })) >= 0.0f)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(m_planes[i], { (xCenter - radius), (yCenter + radius), (zCenter - radius) })) >= 0.0f)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(m_planes[i], { (xCenter + radius), (yCenter + radius), (zCenter - radius) })) >= 0.0f)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(m_planes[i], { (xCenter - radius), (yCenter - radius), (zCenter + radius) })) >= 0.0f)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(m_planes[i], { (xCenter + radius), (yCenter - radius), (zCenter + radius) })) >= 0.0f)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(m_planes[i], { (xCenter - radius), (yCenter + radius), (zCenter + radius) })) >= 0.0f)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(m_planes[i], { (xCenter + radius), (yCenter + radius), (zCenter + radius) })) >= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
}

bool FrustumClass::CheckSphere(float xCenter, float yCenter, float zCenter, float radius)
{
	int i;


	// Check if the radius of the sphere is inside the view frustum.
	for (i = 0; i < 6; i++)
	{
		
		if (XMVectorGetX(XMPlaneDotCoord(m_planes[i], { xCenter, yCenter, zCenter })) < -radius)
		{
			return false;
		}
	}

	return true;
}

bool FrustumClass::CheckRectangle(float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize)
{
	int i;


	// Check if any of the 6 planes of the rectangle are inside the view frustum.
	for (i = 0; i < 6; i++)
	{
		if (XMVectorGetX(XMPlaneDotCoord(m_planes[i], { (xCenter - xSize), (yCenter - ySize), (zCenter - zSize) })) >= 0.0f)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(m_planes[i], { (xCenter + xSize), (yCenter - ySize), (zCenter - zSize) })) >= 0.0f)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(m_planes[i], { (xCenter - xSize), (yCenter + ySize), (zCenter - zSize) })) >= 0.0f)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(m_planes[i], { (xCenter - xSize), (yCenter - ySize), (zCenter + zSize) })) >= 0.0f)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(m_planes[i], { (xCenter + xSize), (yCenter + ySize), (zCenter - zSize) })) >= 0.0f)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(m_planes[i], { (xCenter + xSize), (yCenter - ySize), (zCenter + zSize) })) >= 0.0f)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(m_planes[i], { (xCenter - xSize), (yCenter + ySize), (zCenter + zSize) })) >= 0.0f)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(m_planes[i], { (xCenter + xSize), (yCenter + ySize), (zCenter + zSize) })) >= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
}