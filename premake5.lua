-- EDIT THIS SECTION FOR CUSTOM BUILDS
SPDLOG_INSTALL_DIR = "../AresEngineDependencies/SpdLog/spdlog/"
-- EDIT THIS SECTION FOR CUSTOM BUILDS


BUILD_DIR = "Builds/%{cfg.buildcfg}/%{prj.name}"
INTERMEDIATES_DIR = "Intermediates/%{cfg.buildcfg}/%{prj.name}"

-- include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["spdlog"] = SPDLOG_INSTALL_DIR .. "include"

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
        "_ARESAPI_BUILD_DLL",
    }
	includedirs
	{
        "%{prj.name}/include",
        "%{IncludeDir.spdlog}",
    }
    files
	{
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.cpp",
    }   
    
	filter "configurations:Debug"
        defines "_ARES_DEBUG"
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
    
    defines
    {
        "_ARESAPI_BUILD_DLL",
        "ARES_EDITOR"
    }
    includedirs
    {
        "AresAPI/include",
        "%{IncludeDir.spdlog}",
    }
    files
    {
        "AresAPI/include/**.h",
        "AresAPI/src/**.cpp",
    }
    
    filter "configurations:Debug"
        defines "_ARES_DEBUG"
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
        "%{IncludeDir.spdlog}",
    }
    links
    {
        "AresAPI",
    }
        
    filter "configurations:Debug"
        defines "_ARES_DEBUG"
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
    defines
    {
        "ARES_EDITOR"
    }
    includedirs
    {
        "AresAPI/include",
        "%{IncludeDir.spdlog}",
    }
    links
    {
        "AresEditorAPI"
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
        defines "_ARES_DEBUG"
        runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        runtime "Release"
        optimize "on"
		