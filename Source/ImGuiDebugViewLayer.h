#pragma once
#include <Tbx/PluginAPI/RegisterPlugin.h>
#include <Tbx/Layers/Layer.h>
#include <Tbx/Events/WindowEvents.h>
#include <Tbx/Events/RenderEvents.h>
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
        void OnFrameRendered(const Tbx::RenderedFrameEvent& e) const;
        void OnWindowResized(const Tbx::WindowResizedEvent& e);

        Tbx::Uid _frameRenderedEventId = Tbx::Invalid::Uid;
        Tbx::Uid _windowResizedEventId = Tbx::Invalid::Uid;

        Tbx::Size _windowResolution = { 0, 0 };

        ProcessInfo _processInfo = {};
        SystemInformation _systemInfo = {};

        bool _isDebugWindowOpen = false;
    };

    TBX_REGISTER_PLUGIN(ImGuiDebugViewLayer);
}