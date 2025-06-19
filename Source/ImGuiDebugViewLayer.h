#pragma once
#include <Tbx/Plugin API/RegisterPlugin.h>
#include <Tbx/Layers/Layer.h>
#include <Tbx/Events/WindowEvents.h>
#include <Tbx/Ids/UID.h>
#include <sys_info/ProcessInfo.h>
#include <sys_info/SystemInformation.h>

namespace ImGuiDebugView
{
    class ImGuiDebugViewLayer : public Tbx::ILayerPlugin
    {
    public:
        ImGuiDebugViewLayer() : ILayerPlugin("ImGui") {}

        void OnLoad() override;
        void OnUnload() override;

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        bool IsOverlay() override;

    private:
        void OnWindowResized(const Tbx::WindowResizedEvent& e);

        Tbx::UID _windowResizedEventId = -1;

        Tbx::Size _windowResolution = { 0, 0 };

        ProcessInfo _processInfo = {};
        SystemInformation _systemInfo = {};

        bool _showDebugWindowOnDebugBtnUp = false;
        bool _isDebugWindowOpen = false;
    };

    TBX_REGISTER_PLUGIN(ImGuiDebugViewLayer);
}