#pragma once
#include <Tbx/Collections/LayerStack.h>
#include <Tbx/Events/WindowEvents.h>
#include <Tbx/Events/RenderEvents.h>
#include <Tbx/Events/AppEvents.h>

namespace ImGuiDebugView
{
    class ImGuiDebugViewLayer : public Tbx::Layer
    {
    public:
        ImGuiDebugViewLayer() : Tbx::Layer("ImGui") {}

        /*
        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        */

    private:
        /*
        void OnAppUpdated(const Tbx::WindowResizedEvent& e);
        void OnFrameRendered(const Tbx::RenderedFrameEvent& e);
        void OnWindowResized(const Tbx::WindowResizedEvent& e);
        */

        Tbx::Size _windowResolution = { 0, 0 };
        bool _isDebugWindowOpen = false;
    };
}