#ifndef _POSITIONCLASS_H_
#define _POSITIONCLASS_H_

#define _USE_MATH_DEFINES

#include <cmath>

class PositionClass
{
public:
	PositionClass();
	PositionClass(const PositionClass&);
	~PositionClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	void SetFrameTime(float);
	void GetRotation(float&, float&, float&);
	void GetPosition(float&, float&, float&);

	//cam rotation
	void TurnLeft(bool);
	void TurnRight(bool);
	void TurnUp(bool);
	void TurnDown(bool);

	//cam position
	void GoForeward(bool);
	void GoBackward(bool);
	void GoLeft(bool);
	void GoRight(bool);

private:
	float m_rotationY, m_rotationX, m_rotationZ;
	float m_positionX, m_positionY, m_positionZ;

	float m_frameTime;
	float m_leftTurnSpeed, m_rightTurnSpeed, m_upTurnSpeed, m_downTurnSpeed;
	float m_forewardSpeed, m_rightSpeed;
};

#endif
