
BUILD_DIR = "Builds/%{cfg.buildcfg}/%{prj.name}"
INTERMEDIATES_DIR = "Intermediates/%{cfg.buildcfg}/%{prj.name}"

workspace "AresEngine"
	architecture "x86_64"
	startproject "AresEditor"
	configurations
	{
		"Debug",
		"Release",
    }
    flags
	{
		"MultiProcessorCompile"
	}
	
project "AresAPI"
	location "AresAPI"
	kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"
    systemversion "latest"

	targetdir (BUILD_DIR)
	objdir (INTERMEDIATES_DIR)
    
    defines
    {
        "ARESAPI_BUILD_DLL",
    }
	includedirs
	{
        "%{prj.name}/include",
    }
    files
	{
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.cpp",
    }   
    
	filter "configurations:Debug"
        defines "ARES_DEBUG"
		runtime "Debug"
        symbols "on"
        
	filter "configurations:Release"
		runtime "Release"
        optimize "on"
        
project "AresEditorAPI"
    location "AresEditorAPI"
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"
    systemversion "latest"

    targetdir (BUILD_DIR)
    objdir (INTERMEDIATES_DIR)
        
    files
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.cpp",
    }
    includedirs
    {
        "%{prj.name}/include",
        "AresAPI/include",
    }
    links
    {
        "AresAPI",
    } 
    defines
    {
        "ARESEDITORAPI_BUILD_DLL"
    }
    
    filter "configurations:Debug"
        defines "ARES_DEBUG"
        runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        runtime "Release"
        optimize "on"


project "AresLauncher"
    location "AresLauncher"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"
    systemversion "latest"

    debugdir (BUILD_DIR)
    targetdir (BUILD_DIR)
    objdir (INTERMEDIATES_DIR)

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }
    includedirs
    {
        "AresAPI/include",
    }
    links
    {
        "AresAPI",
    }
        
    filter "configurations:Debug"
        defines "ARES_DEBUG"
        runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        runtime "Release"
        optimize "on"
            
project "AresEditor"
    location "AresEditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"
    systemversion "latest"
    dependson { "AresLauncher" }

    debugdir (BUILD_DIR)
    targetdir (BUILD_DIR)
    objdir (INTERMEDIATES_DIR)

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }
    includedirs
    {
        "AresAPI/include",
        "AresEditorAPI/include",
    }
    links
    {
        "AresEditorAPI",
        "AresAPI",
    }
    postbuildcommands 
	{
        -- copy all the shared Libraries Needed:
        '{COPY} "../Builds/%{cfg.buildcfg}/AresAPI/AresAPI.dll" "%{cfg.targetdir}"',
        '{COPY} "../Builds/%{cfg.buildcfg}/AresEditorAPI/AresEditorAPI.dll" "%{cfg.targetdir}"',

        -- copy launcher executable
        '{COPY} "../Builds/%{cfg.buildcfg}/AresLauncher/AresLauncher.exe" "%{cfg.targetdir}"',
	}
	    
    filter "configurations:Debug"
        defines "ARES_DEBUG"
        runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        runtime "Release"
        optimize "on"
		