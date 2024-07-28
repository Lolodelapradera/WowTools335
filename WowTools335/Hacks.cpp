#include "WindowFrame.h"
#include "MemoryController.h"
#include "Warden.h"


bool AdvanceLuaUnlocker = true;
bool WaterWalking = false;
bool NoFallDmg = false;
bool WallClimb = false;
bool M2Collision1 = false;
bool M2Collision2 = false;
bool WMOCollision = false;
bool ADTCollision = false;
bool AntiAfk = false;
bool AntiknockBack = false;



void DrawHackWindow()
{
    if (ImGui::CollapsingHeader("Hacks"))
    {

      /*  if (Warden::IsApplied)
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
            ImGui::Text("Warden Protection : ON");
        }
        else
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
            ImGui::Text("Warden Protection : OFF");
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip("Warden is the server anti cheat system.");
        }*/
        //ImGui::PopStyleColor();
        //if (!Warden::IsApplied) {
        //    ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        //    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f); // Adjust alpha to make it visually grayed out
        //}

        static ImGuiToggleConfig config = ImGuiTogglePresets::RectangleStyle();

        // Helper function to handle toggles
        auto handleToggle = [](const char* label, auto& patcher, const char* tooltip) {
            // Capture the initial state of the toggle
            bool wasModified = patcher->IsModified;

            // Render the toggle and capture if it was interacted with
            if (ImGui::Toggle(label, &patcher->IsModified, config)) {
                // Check if the state changed due to interaction
                if (patcher->IsModified != wasModified) {
                    if (patcher->IsModified) {
                        patcher->Apply();
                    }
                    else
                    {
                        patcher->Restore();
                    }
                }
            }

            if (ImGui::IsItemHovered() && tooltip) {
                ImGui::SetTooltip(tooltip);
            }
            };

        // Water Walking toggle
        handleToggle("Water Walking", MemoryController::PatcherController["WaterWalking"],
            "When active, allows the user to walk up walls.");
        ImGui::SameLine();
        // Anti-AFK toggle
        handleToggle("Antiafk", MemoryController::PatcherController["AntiAfk"],
            "When active, allows the user to bypass the Afk check.");

        handleToggle("WallClimb", MemoryController::PatcherController["WallClimb"],
            "When active, allows the user to walk up walls.");
        ImGui::SameLine();
        handleToggle("M2Collision", MemoryController::PatcherController["M2Collision"],
            nullptr);

3;

        ImGui::BulletText("Advanced Lua Api");
    }


}

//MemoryController::PatcherController["AntiAfk"]->Restore();
//MemoryController::PatcherController["WaterWalking"]->Restore();
//MemoryController::PatcherController["LuaUnlocker"]->Restore();