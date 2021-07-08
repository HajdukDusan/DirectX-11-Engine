#include "positionclass.h"

PositionClass::PositionClass()
{
	m_frameTime = 0.0f;
	m_rotationY = 0.0f;
	m_rotationX = 30.0f;
	m_leftTurnSpeed = 0.0f;
	m_rightTurnSpeed = 0.0f;
	m_positionX = 0.0f;
	m_positionY = 10.0f;
	m_positionZ = -10.0f;
}


PositionClass::PositionClass(const PositionClass& other)
{

}


PositionClass::~PositionClass()
{
}

void PositionClass::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}


void PositionClass::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}

void PositionClass::SetFrameTime(float time)
{
	m_frameTime = time;
	return;
}

void PositionClass::GetRotation(float& x, float& y, float& z)
{
	x = m_rotationX;
	y = m_rotationY;
	z = m_rotationZ;
	return;
}

void PositionClass::GetPosition(float& x, float& y, float& z)
{
	x = m_positionX;
	y = m_positionY;
	z = m_positionZ;
	return;
}

void PositionClass::GoForeward(bool keydown)
{
	if (keydown)
	{
		m_forewardSpeed += m_frameTime * 0.01f;

		if (m_forewardSpeed > (m_frameTime * 0.10f))
		{
			m_forewardSpeed = m_frameTime * 0.10f;
		}
	}
	else
	{
		m_forewardSpeed -= m_frameTime * 0.005f;

		if (m_forewardSpeed < 0.0f)
		{
			m_forewardSpeed = 0.0f;
		}
	}

	// Update the position
	m_positionZ += m_forewardSpeed * cosf(m_rotationY * M_PI / 180);
	m_positionX += m_forewardSpeed * sinf(m_rotationY * M_PI / 180);
	m_positionY -= m_forewardSpeed * sinf(m_rotationX * M_PI / 180);
}

void PositionClass::GoBackward(bool keydown)
{
	if (keydown)
	{
		m_forewardSpeed -= m_frameTime * 0.01f;

		if (m_forewardSpeed < -(m_frameTime * 0.10f))
		{
			m_forewardSpeed = -m_frameTime * 0.10f;
		}
	}
	else
	{
		m_forewardSpeed += m_frameTime * 0.005f;

		if (m_forewardSpeed > 0.0f)
		{
			m_forewardSpeed = 0.0f;
		}
	}

	// Update the position
	m_positionZ += m_forewardSpeed * cosf(m_rotationY * M_PI / 180);
	m_positionX += m_forewardSpeed * sinf(m_rotationY * M_PI / 180);
	m_positionY -= m_forewardSpeed * sinf(m_rotationX * M_PI / 180);
}

void PositionClass::TurnLeft(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns left.  If not slow down the turn speed.
	if (keydown)
	{
		m_leftTurnSpeed += m_frameTime * 0.01f;

		if (m_leftTurnSpeed > (m_frameTime * 0.15f))
		{
			m_leftTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_leftTurnSpeed -= m_frameTime * 0.005f;

		if (m_leftTurnSpeed < 0.0f)
		{
			m_leftTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationY -= m_leftTurnSpeed;
	if (m_rotationY < 0.0f)
	{
		m_rotationY += 360.0f;
	}
	//float x0 = 0.f;
	//float y0 = 0.f;
	////p'x = cos(theta) * (px-ox) - sin(theta) * (py-oy) + ox
	//m_positionX = cosf(-m_leftTurnSpeed) * (m_positionX - x0) - sinf(-m_leftTurnSpeed) * (m_positionZ - y0) + x0;

	////p'y = sin(theta) * (px-ox) + cos(theta) * (py-oy) + oy
	//m_positionZ = sin(-m_leftTurnSpeed) * (m_positionX - x0) + cos(-m_leftTurnSpeed) * (m_positionZ - y0) + y0;

	return;
}

void PositionClass::TurnRight(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns right.  If not slow down the turn speed.
	if (keydown)
	{
		m_rightTurnSpeed += m_frameTime * 0.01f;

		if (m_rightTurnSpeed > (m_frameTime * 0.15f))
		{
			m_rightTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_rightTurnSpeed -= m_frameTime * 0.005f;

		if (m_rightTurnSpeed < 0.0f)
		{
			m_rightTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationY += m_rightTurnSpeed;
	if (m_rotationY > 360.0f)
	{
		m_rotationY -= 360.0f;
	}

	return;
}

void PositionClass::TurnUp(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns left.  If not slow down the turn speed.
	if (keydown)
	{
		m_upTurnSpeed += m_frameTime * 0.01f;

		if (m_upTurnSpeed > (m_frameTime * 0.15f))
		{
			m_upTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_upTurnSpeed -= m_frameTime * 0.005f;

		if (m_upTurnSpeed < 0.0f)
		{
			m_upTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationX -= m_upTurnSpeed;
	if (m_rotationX < 0.0f)
	{
		m_rotationX += 360.0f;
	}

	return;
}

void PositionClass::TurnDown(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns right.  If not slow down the turn speed.
	if (keydown)
	{
		m_downTurnSpeed += m_frameTime * 0.01f;

		if (m_downTurnSpeed > (m_frameTime * 0.15f))
		{
			m_downTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_downTurnSpeed -= m_frameTime * 0.005f;

		if (m_downTurnSpeed < 0.0f)
		{
			m_downTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationX += m_downTurnSpeed;
	if (m_rotationX > 360.0f)
	{
		m_rotationX -= 360.0f;
	}

	return;
}