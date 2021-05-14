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
	
function LanguageSpecs()
    language "C++"
    cppdialect "C++17"
    staticruntime "off"
    systemversion "latest"
	targetdir (BUILD_DIR)
	objdir (INTERMEDIATES_DIR)
end

function AresAPIShared()
    kind "SharedLib"
    LanguageSpecs()

    defines
    {
        "_ARESAPI_BUILD_DLL",
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
end

project "AresAPI"
	location "AresAPI"
    AresAPIShared()
        
project "AresEditorAPI"
    location "AresEditorAPI"
    AresAPIShared()
    defines
    {
        "ARES_EDITOR"
    }

function ExecutablesShared()
    LanguageSpecs()

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
end

project "AresLauncher"
    location "AresLauncher"
    ExecutablesShared()

    links
    {
        "AresAPI",
    }
                    
project "AresEditor"
    location "AresEditor"
    ExecutablesShared()
    dependson { "AresLauncher" }
    debugdir (BUILD_DIR)
    
    files
    {
        "%{prj.name}/resources.rc",
    }
    defines
    {
        "ARES_EDITOR"
    }
    links
    {
        "AresEditorAPI"
    }
    postbuildcommands 
	{
        -- copy all the shared Libraries Needed:
        '{COPY} "../Builds/%{cfg.buildcfg}/AresEditorAPI/AresEditorAPI.dll" "%{cfg.targetdir}"',
        
        -- copy launcher executable and its dependencies
        '{MKDIR} "%{cfg.targetdir}/GameDeployment"',
        '{COPY} "../Builds/%{cfg.buildcfg}/AresAPI/AresAPI.dll" "%{cfg.targetdir}/GameDeployment"',
        '{COPY} "../Builds/%{cfg.buildcfg}/AresLauncher/AresLauncher.exe" "%{cfg.targetdir}/GameDeployment"',

        -- copy the necessary includes (for scripting)
        '{MKDIR} "%{cfg.targetdir}/Scripting/lib"',
        '{MKDIR} "%{cfg.targetdir}/Scripting/include"',
        
        '{COPY} "../%{IncludeDir.spdlog}" "%{cfg.targetdir}/Scripting/include/spdlog"', 
        '{COPY} "../AresAPI/include" "%{cfg.targetdir}/Scripting/include/AresAPI"',
        
        -- copy the core .lib files so scripting projects can link to them
        '{COPY} "../Builds/%{cfg.buildcfg}/AresEditorAPI/AresEditorAPI.lib" "%{cfg.targetdir}/Scripting/lib"',
        '{COPY} "../Builds/%{cfg.buildcfg}/AresAPI/AresAPI.lib" "%{cfg.targetdir}/Scripting/lib"',
	}
	    
    filter "configurations:Debug"
        postbuildcommands 
        {
            '{COPYFILE} "../Builds/%{cfg.buildcfg}/AresEditorAPI/AresEditorAPI.pdb" "%{cfg.targetdir}"',
        }
		