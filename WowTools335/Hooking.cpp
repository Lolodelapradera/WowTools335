#include "Windows.h"
#include "Hook.h"
#include "Drawing.h"


LPDIRECT3DDEVICE9 Hook::pDevice = nullptr; // Direct3D9 Device Object
tEndScene Hook::oEndScene = nullptr; // Pointer of the original EndScene function
tReset Hook::oReset = nullptr; // Pointer of the original Reset function
HWND Hook::window = nullptr; // Window of the current process
HMODULE Hook::hDDLModule = nullptr; // HMODULE of the DLL

int Hook::windowHeight = 0; // Height of the window
int Hook::windowWidth = 0; // Width of the window
void* Hook::d3d9Device[119]; // Array of pointer of the DirectX functions.
WNDPROC Hook::OWndProc = nullptr; // Pointer of the original window message handler.

inline HWND GetGameWindow()
{ 
	return *(HWND*)0x00D41620; 
}
void Hook::HookDirectX()
{

	if (GetD3D9Device(d3d9Device, sizeof(d3d9Device)))
	{
		oEndScene = (tEndScene)d3d9Device[42];
		oReset = (tReset)d3d9Device[16];

		DetourTransactionBegin();


		DetourUpdateThread(GetCurrentThread());

		DetourAttach(&(PVOID&)oEndScene, Drawing::hkEndScene);

		DetourTransactionCommit();
	}
}

/**
	@brief : Function that unhook Reset and EnScene functions, and also disable the window message handler.
**/
void Hook::UnHookDirectX()
{
	if (Drawing::bInit)
	{
		UnHookWindow();
		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
		UnhookWindowsHookEx(keyboardHook);
	}

	Drawing::bInit = FALSE;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)oEndScene, Drawing::hkEndScene);
	DetourTransactionCommit();
}

	#pragma region Window Helper



BOOL CALLBACK Hook::enumWind(const HWND handle, LPARAM lp)
{
	DWORD procID;
	GetWindowThreadProcessId(handle, &procID);
	if (GetCurrentProcessId() != procID)
		return TRUE;

	window = handle;
	return FALSE;
}

HWND Hook::GetProcessWindow()
{
	window = nullptr;

	EnumWindows(enumWind, NULL);

	RECT size;
	if (window == nullptr)
		return nullptr;

	GetWindowRect(window, &size);

	windowWidth = size.right - size.left;
	windowHeight = size.bottom - size.top;

	windowHeight -= 29;
	windowWidth -= 5;

	return window;
}

BOOL Hook::GetD3D9Device(void** pTable, const size_t size)
{
	if (!pTable)
		return FALSE;

	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!pD3D)
		return FALSE;

	IDirect3DDevice9* pDummyDevice = nullptr;

	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.Windowed = FALSE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GetProcessWindow();

	if (HRESULT dummyDevCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice); dummyDevCreated != S_OK)
	{
		d3dpp.Windowed = !d3dpp.Windowed;
		dummyDevCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

		if (dummyDevCreated != S_OK)
		{
			pD3D->Release();
			return FALSE;
		}
	}

	memcpy(pTable, *(void***)(pDummyDevice), size);
	pDummyDevice->Release();
	pD3D->Release();
	return TRUE;
}

void Hook::HookWindow()
{
	OWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
}

void Hook::UnHookWindow()
{
	SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)OWndProc);
}

LRESULT WINAPI Hook::WndProc(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam)
{
	if (Drawing::bDisplay && ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
	{
		return true;
	}

	if (msg == WM_KEYDOWN && wParam == VK_F5)
	{
		Drawing::bDisplay = !Drawing::bDisplay;
	}
	


	if (msg == WM_CLOSE)
	{
		UnHookDirectX();
		UnHookWindow();
		TerminateProcess(GetCurrentProcess(), 0);
	}

	if (msg == WM_DESTROY)
	{
		Drawing::bSetPos = true;
		UnHookWindow();
		Drawing::bInit = FALSE;
		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
		return true;
	}

	if (msg == EVENT_SYSTEM_DESKTOPSWITCH)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
	}

	ImGuiIO& io = ImGui::GetIO();

	POINT mPos;
	GetCursorPos(&mPos);

	switch (msg)
	{
	case WM_SIZE:
		if (wParam == SIZE_RESTORED || wParam == SIZE_MINIMIZED || wParam == SIZE_MAXIMIZED)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
		}
		break;
	}
	// Let ImGui handle mouse input if needed, but only when the mouse is hovering over an ImGui window.
	if (Drawing::bDisplay)
	{
		if (io.WantCaptureKeyboard || io.WantCaptureMouse)
			return true;
	}

	// Call the original window procedure for other messages.
	return CallWindowProc(OWndProc, hWnd, msg, wParam, lParam);
}

	#pragma endregion