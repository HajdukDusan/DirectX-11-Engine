#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_

#define DIRECTINPUT_VERSION 0x0800


// Linking for Direct input to work
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#include <dinput.h>

class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	bool Frame();

	bool IsEscapePressed();
	void GetMouseLocation(int&, int&);

	bool IsUpArrowPressed();
	bool IsDownArrowPressed();
	bool IsLeftArrowPressed();
	bool IsRightArrowPressed();

	bool IsWPressed();
	bool IsSPressed();

	bool IsLeftMouseButtonDown();


	bool IsF1Toggled();

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

private:
	IDirectInput8* m_directInput; // the interface to Direct Input
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;

public:
	//Used for recording the keyboard and mouse states
	unsigned char m_keyboardState[256];

private:
	DIMOUSESTATE m_mouseState;

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;


	bool m_F1_released;
};


#endif