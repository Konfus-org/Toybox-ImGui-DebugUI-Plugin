#pragma once
#include <Tbx/Plugins/Plugin.h>
#include <Tbx/Layers/Layer.h>
#include <Tbx/Events/WindowEvents.h>
#include <Tbx/Events/RenderEvents.h>
#include <Tbx/Ids/Uid.h>

namespace ImGuiDebugView
{
    /*class ImGuiDebugViewLayer : public Tbx::ILayerPlugin
    {
    public:
        ImGuiDebugViewLayer(const std::weak_ptr<Tbx::App>& app) : ILayerPlugin("ImGui", app) {}

        void OnLoad() override;
        void OnUnload() override;

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;

    private:
        void OnFrameRendered(const Tbx::RenderedFrameEvent& e);
        void OnWindowResized(const Tbx::WindowResizedEvent& e);

        Tbx::Size _windowResolution = { 0, 0 };
        bool _isDebugWindowOpen = false;
    };

    TBX_REGISTER_PLUGIN(ImGuiDebugViewLayer);*/
}