#include "ImGuiDebugViewPlugin.h"
#include "ImGuiDebugViewLayer.h"
#include <Tbx/App/App.h>
#include <imgui.h>

namespace ImGuiDebugView
{
    void ImGuiDebugViewPlugin::OnLoad()
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        // Add our imgui layer
        _app.lock()->AddLayer<ImGuiDebugViewLayer>();
    }

    void ImGuiDebugViewPlugin::OnUnload()
    {
        ImGui::DestroyContext();
    }
}
