#pragma once
#include <Tbx/PluginAPI/RegisterPlugin.h>
#include <Tbx/Layers/Layer.h>
#include <Tbx/Events/WindowEvents.h>
#include <Tbx/Events/RenderEvents.h>
#include <Tbx/Ids/UID.h>

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
        void OnFrameRendered(const Tbx::RenderedFrameEvent& e);
        void OnWindowResized(const Tbx::WindowResizedEvent& e);

        Tbx::Size _windowResolution = { 0, 0 };
        bool _isDebugWindowOpen = false;
    };

    TBX_REGISTER_PLUGIN(ImGuiDebugViewLayer);
}