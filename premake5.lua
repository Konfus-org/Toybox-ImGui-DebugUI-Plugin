project "ImGui Debug UI"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "Off"

    files
    {
        "./**.hpp",
        "./**.cpp",
        "./**.h",
        "./**.c",
        "./**.md",
        "./**.plugin"
    }
    includedirs
    {
        "./Source",

        -- ImGui includes
        _MAIN_SCRIPT_DIR .. "/Dependencies/ImGui",
        _MAIN_SCRIPT_DIR .. "/Dependencies/ImGui/backends",

        -- sys_info includes
        _MAIN_SCRIPT_DIR .. "/Dependencies/sys_info/core/include",

        -- SDL includes
        _MAIN_SCRIPT_DIR .. "/Dependencies/SDL3/include"
    }
    links
    {
        "ImGui",
        "sys_info",
        "SDL3"
    }

    RegisterDynamicPlugin("ImGui Debug UI")
