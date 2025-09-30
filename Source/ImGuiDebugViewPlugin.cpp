#include "ImGuiDebugViewPlugin.h"
#include "ImGuiDebugViewLayer.h"
#include <Tbx/App/App.h>
#include <imgui.h>

namespace ImGuiDebugView
{
    ImGuiDebugViewPlugin::ImGuiDebugViewPlugin(Tbx::Ref<Tbx::EventBus> eventBus)
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

		// TODO: Do this through an app initialized event
        // Add our imgui layer
        //app.lock()->AddLayer<ImGuiDebugViewLayer>();
    }

    ImGuiDebugViewPlugin::~ImGuiDebugViewPlugin()
    {
        ImGui::DestroyContext();
    }
}
