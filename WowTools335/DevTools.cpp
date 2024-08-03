#include "Headers.h"
#include "WindowFrame.h"
#include <cstdio>

bool ConsoleAppLoaded = false;
void DeveloperTools()
{
	if (ImGui::CollapsingHeader("Developer Tools"))
	{
		if (ImGui::Button("Console App"))
		{
			if (!ConsoleAppLoaded)
			{
				AllocConsole();
				FILE* stream;
				freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
				freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
				freopen_s(&stream, "CONOUT$", "w", stdout);
				ConsoleAppLoaded = true;
			}
		}
	}
}