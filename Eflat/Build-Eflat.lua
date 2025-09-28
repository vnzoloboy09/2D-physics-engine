project "Eflat"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    targetdir "Binaries/%{cfg.buildcfg}"
    staticruntime "off"
    
    buildoptions "/utf-8"

    files 
    { 
        "src/**.h", 
        "src/**.cpp" 
    }
    
    pchheader "efpch.h"
    pchsource "src/efpch.cpp"

    includedirs
    {
        "vendor/raylib/include",
        "vendor/spdlog/include",
        "src"
    }

    libdirs 
    {
        "vendor/raylib"
    }

    links
    {
        "raylib",
        "winmm"
    }

    targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

    filter "system:windows"
        systemversion "latest"
        defines { }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        defines { "DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"