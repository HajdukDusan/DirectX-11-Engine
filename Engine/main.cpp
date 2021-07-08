#include "systemclass.h"
#include "d3dclass.h"
#include "scenerenderclass.h"


#include "guiclass.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"

D3DClass*			DX;
GuiClass*			GUI;
SceneRenderClass*	Scene;

static int* mouseInput = new int[5];

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"Engine", NULL };
	::RegisterClassEx(&wc);
	HWND hwnd = ::CreateWindow(wc.lpszClassName, L"DirectX11 Engine", WS_OVERLAPPEDWINDOW, 0, 0, 1920, 1080, NULL, NULL, wc.hInstance, NULL);

	// Initialize Direct3D
	DX = new D3DClass;
	if (!DX->Initialize(1920, 1080, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR)) {
		DX->Shutdown();
		::UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 1;
		// error
	}

	// Setup Scene
	Scene = new SceneRenderClass(DX, hwnd);


	// Setup GUI
	GUI = new GuiClass(hwnd, DX);

	// Show the window
	::ShowWindow(hwnd, SW_MAXIMIZE); // maximize window
	::UpdateWindow(hwnd);

	// Main loop
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (msg.message != WM_QUIT)
	{
		if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			continue;
		}


		// Update mouse input
		GUI->GetMouseInput(mouseInput);

		// render to texture
		if (!Scene->RenderScene(DX, mouseInput)) {
			GUI->PrintConsole("[error] Unexpected error while rendering scene to texture.");
			exit(-1);
		}

		// Begin rendering for gui
		DX->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

		// Render the gui
		GUI->Render(Scene);


		// Present everything
		DX->PresentScene();

	}

	// Cleanup everything
	delete GUI;
	delete mouseInput;
	DX->Shutdown();
	::DestroyWindow(hwnd);
	::UnregisterClass(wc.lpszClassName, wc.hInstance);


	return 0;
}



#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0 // From Windows SDK 8.1+ headers
#endif

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (DX->GetDevice() != NULL && wParam != SIZE_MINIMIZED)
		{
			DX->CleanupRenderTarget();
			DX->GetSwapChain()->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
			DX->CreateRenderTarget();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	case WM_DPICHANGED:
		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
		{
			//const int dpi = HIWORD(wParam);
			//printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
			const RECT* suggested_rect = (RECT*)lParam;
			::SetWindowPos(hWnd, NULL, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
		}
		break;
	}
	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}