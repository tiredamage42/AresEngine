-- EDIT THIS SECTION FOR CUSTOM BUILDS
SPDLOG_INSTALL_DIR = "../AresEngineDependencies/SpdLog/spdlog/"
GLFW_INSTALL_DIR = "../AresEngineDependencies/GLFW/glfw/"
GLAD_INSTALL_DIR = "../AresEngineDependencies/Glad/"
IMGUI_INSTALL_DIR = "../AresEngineDependencies/IMGUI/imgui/"
-- EDIT THIS SECTION FOR CUSTOM BUILDS

BUILD_DIR = "Builds/%{cfg.buildcfg}/%{prj.name}"
INTERMEDIATES_DIR = "Intermediates/%{cfg.buildcfg}/%{prj.name}"

-- include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["spdlog"] = SPDLOG_INSTALL_DIR .. "include"
IncludeDir["GLFW"] = GLFW_INSTALL_DIR .. "include"
IncludeDir["Glad"] = GLAD_INSTALL_DIR .. "include"
IncludeDir["ImGui"] = IMGUI_INSTALL_DIR .. "include"

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
        "GLFW_INCLUDE_NONE",
    }
    includedirs
	{
        "AresAPI/include",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
    }
    files
	{
        "AresAPI/include/**.h",
        "AresAPI/src/**.cpp",
    }
    links
    {
        "opengl32.lib",
        GLFW_INSTALL_DIR .. "src/%{cfg.buildcfg}/glfw3.lib",
        GLAD_INSTALL_DIR .. "%{cfg.buildcfg}/Glad.lib",
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
        "ARES_EDITOR",
        "_ARESAPI_BUILD_DLL",
        "GLFW_INCLUDE_NONE",
    }
    includedirs
	{
        "AresAPI/include",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
    }
    files
	{
        "AresAPI/include/**.h",
        "AresAPI/src/**.cpp",
    }
    links
    {
        "opengl32.lib",
        GLFW_INSTALL_DIR .. "src/%{cfg.buildcfg}/glfw3.lib",
        GLAD_INSTALL_DIR .. "%{cfg.buildcfg}/Glad.lib",
        IMGUI_INSTALL_DIR .. "%{cfg.buildcfg}/ImGui.lib",   
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
    dependson { "AresLauncher" }
    debugdir (BUILD_DIR)
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
        "%{prj.name}/resources.rc",
    }
    includedirs
    {
        "AresAPI/include",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.ImGui}",
    }
    defines
    {
        "ARES_EDITOR"
    }
    links
    {
        "AresEditorAPI",
        IMGUI_INSTALL_DIR .. "%{cfg.buildcfg}/ImGui.lib",
    }
    postbuildcommands 
	{
        -- copy all the shared Libraries Needed:
        '{COPY} "../Builds/%{cfg.buildcfg}/AresEditorAPI/AresEditorAPI.dll" "%{cfg.targetdir}"',
        '{COPY} "../' .. IMGUI_INSTALL_DIR .. '%{cfg.buildcfg}/ImGui.dll" "%{cfg.targetdir}"',

        -- copy needed resources
        '{COPY} "../AresEditor/EditorData" "%{cfg.targetdir}/EditorData"',

        -- copy launcher executable and its dependencies
        '{MKDIR} "%{cfg.targetdir}/GameDeployment"',
        '{COPY} "../Builds/%{cfg.buildcfg}/AresAPI/AresAPI.dll" "%{cfg.targetdir}/GameDeployment"',
        '{COPY} "../Builds/%{cfg.buildcfg}/AresLauncher/AresLauncher.exe" "%{cfg.targetdir}/GameDeployment"',

        -- copy the necessary includes (for scripting)
        '{MKDIR} "%{cfg.targetdir}/Scripting/include"',
        '{COPY} "../%{IncludeDir.imgui}" "%{cfg.targetdir}/Scripting/includes/imgui"', 
        '{COPY} "../%{IncludeDir.spdlog}" "%{cfg.targetdir}/Scripting/include/spdlog"', 
        '{COPY} "../AresAPI/include" "%{cfg.targetdir}/Scripting/include/AresAPI"',
        
        -- copy the core .lib files so scripting projects can link to them
        '{MKDIR} "%{cfg.targetdir}/Scripting/lib"',
        '{COPY} "../Builds/%{cfg.buildcfg}/AresEditorAPI/AresEditorAPI.lib" "%{cfg.targetdir}/Scripting/lib"',
        '{COPY} "../Builds/%{cfg.buildcfg}/AresAPI/AresAPI.lib" "%{cfg.targetdir}/Scripting/lib"',
        '{COPY} "../' .. IMGUI_INSTALL_DIR .. '%{cfg.buildcfg}/ImGui.lib" "%{cfg.targetdir}/Scripting/lib"',
	}
    filter "configurations:Debug"
        kind "ConsoleApp"
        defines "_ARES_DEBUG"
        runtime "Debug"
        symbols "on"
        postbuildcommands 
        {
            '{COPY} "../Builds/%{cfg.buildcfg}/AresEditorAPI/AresEditorAPI.pdb" "%{cfg.targetdir}"',
        }
    filter "configurations:Release"
        kind "WindowedApp"
        entrypoint "mainCRTStartup"
        runtime "Release"
        optimize "on"
        postbuildcommands 
        {
            '{DELETE} "%{cfg.targetdir}/%{prj.name}.pdb"'
        }