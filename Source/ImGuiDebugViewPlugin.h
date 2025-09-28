#pragma once
#include <Tbx/Plugins/Plugin.h>

namespace ImGuiDebugView
{
    class ImGuiDebugViewPlugin final : public Tbx::Plugin
    {
    public:
        ImGuiDebugViewPlugin(Tbx::WeakRef<Tbx::App> app);
        ~ImGuiDebugViewPlugin() override;
    };

    TBX_REGISTER_PLUGIN(ImGuiDebugViewPlugin);
}