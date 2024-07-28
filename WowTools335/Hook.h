#pragma once
#pragma once


#ifndef HOOK_H
#define HOOK_H

#include "Headers.h"


using tEndScene = HRESULT(APIENTRY*)(LPDIRECT3DDEVICE9 pDevice);
using tReset = HRESULT(APIENTRY*)(D3DPRESENT_PARAMETERS* pPresentationParameters);
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
HHOOK keyboardHook;
inline HWND GetGameWindow();

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


class Hook
{
public:
	static IDirect3DDevice9* pDevice;
	static tEndScene oEndScene;
	static HWND window;
	static HMODULE hDDLModule;
	static void HookDirectX();
	static void UnHookDirectX();
	static void HookWindow();
	static void UnHookWindow();


	

private:
	static int windowHeight, windowWidth;
	static void* d3d9Device[119];
	static WNDPROC OWndProc;
	static tReset oReset;

	static BOOL CALLBACK enumWind(HWND handle, LPARAM lp);
	static HWND GetProcessWindow();
	static BOOL GetD3D9Device(void** pTable, size_t size);
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static HRESULT __stdcall hkReset(D3DPRESENT_PARAMETERS* pPresentationParameters);
};

#endif

