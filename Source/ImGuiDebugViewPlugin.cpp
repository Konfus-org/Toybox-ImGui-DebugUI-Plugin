#include "ImGuiDebugViewPlugin.h"
#include "ImGuiDebugViewLayer.h"
#include <Tbx/App/App.h>
#include <imgui.h>

namespace ImGuiDebugView
{
    ImGuiDebugViewPlugin::ImGuiDebugViewPlugin(Tbx::WeakRef<Tbx::App> app)
        : Tbx::Plugin(app)
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        // Add our imgui layer
        app.lock()->AddLayer<ImGuiDebugViewLayer>();
    }

    ImGuiDebugViewPlugin::~ImGuiDebugViewPlugin()
    {
        ImGui::DestroyContext();
    }
}
