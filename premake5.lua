project "ImGui UI"
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
        "./**.h",
        "./**.c",
        "./**.hpp",
        "./**.cpp"
    }

    defines
    {
        "IMGUI_IMPL_OPENGL_ES3"
    }

    includedirs
    {
        "./Source",
        "./3rd Party/ImGui",
        "./3rd Party/ImGui/backends",
        "./3rd Party/sys_info"
    }

    links
    {
        "ImGui",
        "sys_info"
    }

    ToyboxPluginConfigs()
    RegisterPlugin("ImGui UI")
