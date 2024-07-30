#include "Drawing.h"
#include "Hook.h"
#include "WindowFrame.h"
#include "RegisteredFunc.h"
#include <iostream>

bool Drawing::bInit = false; // Status of the initialization of ImGui.
bool Drawing::bDisplay = false; // Status of the menu display.
bool Drawing::bSetPos = false; // Status to update ImGui window size / position.
bool Drawing::packet = false;
ImVec2 Drawing::vWindowPos = { 0, 0 }; // Last ImGui window position.
ImVec2 Drawing::vWindowSize = { 0, 0 }; // Last ImGui window size.


void callLuaFunctionsAndRemoveFromCallback()
{
	if (CallBack.empty())
		return;

	auto L = GetLuaState();

	for (auto it = CallBack.begin(); it != CallBack.end(); ) {
		const std::string& functionName = *it;

		lua_getglobal(L, functionName.c_str());  // Get function from global environment

		if (lua_type(L, -1) == LUA_TFUNCTION) {  // Check if it's a function
			if (lua_pcall(L, 0, 0, 0) != 0) {  // Call the function with no arguments
				const char* errorMessage = lua_tostring(L, -1);
				std::cerr << "Error calling function " << functionName << ": " << errorMessage << std::endl;
				lua_pop(L, 1);  // Pop the error message
			}
			else {
				std::cout << "Function " << functionName << " called successfully." << std::endl;
				it = CallBack.erase(it);  // Remove function name from CallBack
				continue;  // Skip incrementing `it`
			}
		}

		lua_pop(L, 1);  // Pop the function from stack
		++it;  // Move to next function name
	}

}


HRESULT Drawing::hkEndScene(const LPDIRECT3DDEVICE9 D3D9Device)
{

	if (!Hook::pDevice)
		Hook::pDevice = D3D9Device;
	if (!Drawing::bInit)
		InitImGui(D3D9Device);

	callLuaFunctionsAndRemoveFromCallback();
	

	if (bDisplay)
	{

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::SetNextWindowSize({ (float)400, (float)400 }, ImGuiCond_Once);
		if (ImGui::Begin("WowTools", &bDisplay))
		{
			DrawHackWindow();
		}
		ImGui::End();

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}

	return Hook::oEndScene(D3D9Device);
}

void Drawing::InitImGui(const LPDIRECT3DDEVICE9 pDevice)
{
	if (!bInit)
	{
		D3DDEVICE_CREATION_PARAMETERS CP;
		pDevice->GetCreationParameters(&CP);
		Hook::window = GetGameWindow();
		Hook::HookWindow();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.IniFilename = nullptr;

		io.Fonts->AddFontDefault();
		io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 27.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());

		// Set ImGui configuration flags
		io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
		io.ConfigFlags |= ImGuiConfigFlags_NavNoCaptureKeyboard;


		ImGui::StyleColorsDark();
		ImGui_ImplWin32_Init(Hook::window);
		ImGui_ImplDX9_Init(pDevice);
		bInit = true;
	}
}
