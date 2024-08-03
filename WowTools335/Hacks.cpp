#include "Headers.h"
#include "MemoryController.h"
#include "Warden.h"
#include "WindowFrame.h"



//bool AdvanceLuaUnlocker = true;
//bool WaterWalking = false;
//bool NoFallDmg = false;
//bool WallClimb = false;
//bool M2Collision1 = false;
//bool M2Collision2 = false;
//bool WMOCollision = false;
//bool ADTCollision = false;
//bool AntiAfk = false;
//bool AntiknockBack = false;



void DrawHackWindow()
{
    if (ImGui::CollapsingHeader("Hacks"))
    {
        auto handleToggle = [](const char* label, auto& patcher, const char* tooltip)
            {
                // Ensure patcher is not null
                if (!patcher) {
                    ImGui::Text("Invalid patcher for %s", label);
                    return;
                }

                // Capture the initial state of the toggle
                bool wasModified = patcher->IsModified;

                // Render the toggle and capture if it was interacted with
                if (ImGui::Checkbox(label, &patcher->IsModified))
                {
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



        // Set the text color based on the Warden status
        ImVec4 textColor = Warden::IsApplied ? ImVec4(0.0f, 1.0f, 0.0f, 1.0f) : ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
        ImGui::PushStyleColor(ImGuiCol_Text, textColor);

        // Display Warden status
        ImGui::Text("Warden Protection : %s", Warden::IsApplied ? "ON" : "OFF");

        // Show tooltip on hover
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip("Warden is the server anti-cheat system.");
        }

        ImGui::PopStyleColor(); // Restore previous text color

        // Disable UI elements if Warden is not applied
        ImGui::BeginDisabled(!Warden::IsApplied);

        // Helper function to handle toggles
      

        // Water Walking toggle
        handleToggle("Water Walking     ", MemoryController::PatcherController["WaterWalking"],
            "When active, allows the user to walk up walls.");
        ImGui::SameLine();
        // Anti-AFK toggle
        handleToggle("Antiafk", MemoryController::PatcherController["AntiAfk"],
            "When active, allows the user to bypass the Afk check.");

        handleToggle("WallClimb         ", MemoryController::PatcherController["WallClimb"],
            "When active, allows the user to walk up walls.");
        ImGui::SameLine();
        handleToggle("M2Collision", MemoryController::PatcherController["M2Collision"],
            nullptr);

        handleToggle("Anti KnockBack    ", MemoryController::PatcherController["AntiKnock"],
            "Anti-knock prevents you from being knocked back.");
        ImGui::SameLine();
       /* handleToggle("No Fall Damage", MemoryController::PatcherController["NoFallDamage"],
            "No Fall Damage protects you from any injury when falling.");*/
        handleToggle("Infinite Jump", MemoryController::PatcherController["InfiniteJump"],
            "Infinite Jump enables unlimited jumping.");
        handleToggle("Flying", MemoryController::PatcherController["Flying"],
            "allowing the player to fly");
        //Flying

        ImGui::BulletText("Advanced Lua Api");
        ImGui::BulletText("AVR Patch ");
        ImGui::BulletText("Language Patch");

        ImGui::EndDisabled();
    }
}

//MemoryController::PatcherController["AntiAfk"]->Restore();
//MemoryController::PatcherController["WaterWalking"]->Restore();
//MemoryController::PatcherController["LuaUnlocker"]->Restore();