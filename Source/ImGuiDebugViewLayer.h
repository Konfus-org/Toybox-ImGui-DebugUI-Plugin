#pragma once
#include <Tbx/Layers/Layer.h>
#include <Tbx/Events/WindowEvents.h>
#include <Tbx/Events/RenderEvents.h>

namespace ImGuiDebugView
{
    class ImGuiDebugViewLayer : public Tbx::Layer
    {
    public:
        ImGuiDebugViewLayer() : Tbx::Layer("ImGui") {}

        /*void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;*/

    private:
        /*void OnFrameRendered(const Tbx::RenderedFrameEvent& e);
        void OnWindowResized(const Tbx::WindowResizedEvent& e);*/

        Tbx::Size _windowResolution = { 0, 0 };
        bool _isDebugWindowOpen = false;
    };
}