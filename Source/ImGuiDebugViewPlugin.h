#pragma once
#include <Tbx/Plugins/Plugin.h>

namespace ImGuiDebugView
{
    class ImGuiDebugViewPlugin : public Tbx::Plugin
    {
    public:
        ImGuiDebugViewPlugin(Tbx::WeakRef<Tbx::App> app)
            : _app(app) {}

        void OnLoad() final;
        void OnUnload() final;

    private:
        Tbx::WeakRef<Tbx::App> _app = {};
    };

    TBX_REGISTER_PLUGIN(ImGuiDebugViewPlugin);
}