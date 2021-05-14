-- EDIT THIS SECTION FOR CUSTOM BUILDS
SPDLOG_INSTALL_DIR = "../AresEngineDependencies/SpdLog/spdlog/"
GLFW_INSTALL_DIR = "../AresEngineDependencies/GLFW/glfw/"
-- EDIT THIS SECTION FOR CUSTOM BUILDS


BUILD_DIR = "Builds/%{cfg.buildcfg}/%{prj.name}"
INTERMEDIATES_DIR = "Intermediates/%{cfg.buildcfg}/%{prj.name}"

-- include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["spdlog"] = SPDLOG_INSTALL_DIR .. "include"
IncludeDir["GLFW"] = GLFW_INSTALL_DIR .. "include"

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
        "%{IncludeDir.GLFW}",
    }
    files
	{
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.cpp",
    }   

    libdirs
    {
        GLFW_INSTALL_DIR .. "src/%{cfg.buildcfg}",
    }
    links
    {
        "glfw3.lib",
        "opengl32.lib",
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
        "%{IncludeDir.GLFW}",
    }
    files
    {
        "AresAPI/include/**.h",
        "AresAPI/src/**.cpp",
    }

    libdirs
    {
        GLFW_INSTALL_DIR .. "src/%{cfg.buildcfg}",
    }
    links
    {
        "glfw3.lib",
        "opengl32.lib",
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
        kind "ConsoleApp"
        defines "_ARES_DEBUG"
        runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        kind "WindowedApp"
        entrypoint "mainCRTStartup"
        runtime "Release"
        optimize "on"
            
project "AresEditor"
    location "AresEditor"
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
        "%{prj.name}/resources.rc",
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
        kind "ConsoleApp"
        defines "_ARES_DEBUG"
        runtime "Debug"
        symbols "on"
        postbuildcommands 
        {
            '{COPY} "../Builds/%{cfg.buildcfg}/AresAPI/AresAPI.pdb" "%{cfg.targetdir}"',
            '{COPY} "../Builds/%{cfg.buildcfg}/AresEditorAPI/AresEditorAPI.pdb" "%{cfg.targetdir}"',
        }
        
    filter "configurations:Release"
        kind "WindowedApp"
        entrypoint "mainCRTStartup"
        runtime "Release"
        optimize "on"
		