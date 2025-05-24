project "ImGui Debug UI"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "Off"
    ignoredefaultlibraries { "MSVCRT" }
    externalwarnings "Off"

    targetdir ("../../" .. OutputTargetPluginDir .. "")
    objdir    ("../../" .. OutputIntermediatePluginDir .. "")

    files
    {
        "./Source/**.h",
        "./Source/**.c",
        "./Source/**.cc",
        "./Source/**.hpp",
        "./Source/**.cpp",
        "./Include/**.h",
        "./Include/**.c",
        "./Include/**.cc",
        "./Include/**.hpp",
        "./Include/**.cpp",
        "./**.plugin",
        "./**.md",
        "./*.lua"
    }

    defines
    {
        "IMGUI_IMPL_OPENGL_ES3"
    }

    includedirs
    {
        "./Source",
        "%{Using.ImGui}",
        "%{Using.ImGuiBackends}",
        "%{Using.sys_info}"
    }

    links
    {
        "ImGui",
        "sys_info"
    }

    ToyboxPluginConfigs()
    RegisterPlugin("ImGui Debug UI")
