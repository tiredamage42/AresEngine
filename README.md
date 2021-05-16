# AresEngine
A game engine based off [The Cherno's Hazel Engine](https://github.com/TheCherno/Hazel).

>Uses OpenGL as a rendering backend.

>Currently only supports Windows.
## Engine Components
<hr>

**AresAPI [Shared Library]-** Contains all the base functionality for the engine.

**AresEditor [Executable]-** Program to edit Ares projects.

**AresEditorAPI [Shared Library]-** Same codebase as AresAPI, but contains all the editor functionality enabled, so projects can make custom editor windows, custom component field visualizations, etc.

**AresLauncher [Executable]-** Program used to launch Ares projects (game launcher)

## Getting / Building Dependencies
<hr>

**Visual Studio 2019**

Building AresEngine requires [Visual Studio 2019](https://visualstudio.microsoft.com/downloads/)

**spdlog**
```
$ git clone https://github.com/gabime/spdlog.git
```
**GLFW**
```
$ git clone https://github.com/glfw/glfw.git
$ cd glfw
$ cmake . -DUSE_MSVC_RUNTIME_LIBRARY_DLL=ON
$ cmake --build . --config Debug
$ cmake --build . --config Release
```
**Glad**
1. Go to: https://glad.dav1d.de/ and choose the following configuration:
   ![GladSpecs](Documentation/GladSpecs.png)
2. Click Generate
3. Click on Glad.zip to download.
4. in extracted directory, create a file called ```premake5.lua```:
    ```lua
    workspace "Glad"
        architecture "x86_64"
        configurations
        {
            "Debug",
            "Release",
        }
        flags
        {
            "MultiProcessorCompile"
        }
    project "Glad"
        kind "StaticLib"
        language "C"
        staticruntime "off"
        systemversion "latest"
        targetdir ("%{cfg.buildcfg}")
        objdir ("Intermediates/%{cfg.buildcfg}")
        files
        {
            "include/glad/glad.h",
            "include/KHR/khrplatform.h",
            "src/glad.c",
        }
        includedirs "include"
        filter "configurations:Debug"
            runtime "Debug"
            symbols "on"
        filter "configurations:Release"
            runtime "Release"
            optimize "on"
    ```
5. In the same directory, open a command prompt and create the visual studio project with premake:
   > There is a premake exectuable included in this repo, use the path to that for this step.
   ```
   $ path\to\AresEngine\Premake\premake5.exe vs2019
   ```
6. Build the ```Debug``` and ```Release``` configurations.

**ImGui**

1. 
   ```
   $ git clone -b docking --single-branch https://github.com/ocornut/imgui.git
   ```

2. In ```imconfig.h```:

	Replace:
    ```c++
    //#define IMGUI_API __declspec( dllexport )
    //#define IMGUI_API __declspec( dllimport )
    ```
	with:
    ```c++
    #ifdef IMGUI_BUILD_DLL
        #define IMGUI_API __declspec(dllexport)
    #else
        #define IMGUI_API __declspec(dllimport)
    #endif
    ```
3. In the repository's root directory, create a file called ```premake5.lua```:
   ```lua
    workspace "ImGui"
	    architecture "x86_64"	
	    configurations
	    {
            "Debug",
            "Release",
        }
        flags
        {
            "MultiProcessorCompile"
        }
    project "ImGui"
	    kind "SharedLib"
        language "C++"
        cppdialect "C++17"
        staticruntime "off"
	    systemversion "latest"
        targetdir ("%{cfg.buildcfg}")
        objdir ("Intermediates/%{cfg.buildcfg}")
        defines
        {
            "IMGUI_BUILD_DLL"
        }
        includedirs
        {
            "include",
        }
        files
        {
            "include/**.h",
            "src/**.cpp",
        }
        filter "configurations:Debug"
            runtime "Debug"
            symbols "on"
        filter "configurations:Release"
            runtime "Release"
            optimize "on"
   ```
4. Put all the .h files into a new folder called ```include``` and the .cpp files into a new folder called ```src```.

5. In the repository's root directory, open a command prompt and create the visual studio project with premake:
   > There is a premake exectuable included in this repo, use the path to that for this step.
   ```
   $ path\to\AresEngine\Premake\premake5.exe vs2019
   ```
6. Build the ```Debug``` and ```Release``` configurations.

## Building The Engine
<hr>

1. Update the install directories of all the dependences at the top of ```premake5.lua```.
2. Run ```GenerateProject.bat```.
3. Build the ```AresEditor``` project.
4. All the required files and libraries for the engine will be in ```Builds\Release\AresEditor\``` (or ```Builds\Debug\AresEditor\``` depending on the configuration you build)

<hr><br><br><br><hr>

# Scripting
## Common Defines
| Define | Description |
| --- | --- |
| ARES_EDITOR | Defined only in the context of the editor. When defined you can use ```AresEditor``` namespace classes. |
<hr>

## Class ```Ares::Application```
| Method | Description |
| --- | --- |
| static void Close | Close the currently running application |
<hr>

## Class ```Ares::Debug```
All log messages are saved to a text file called ```Ares.log``` in the install directory of the executable being run (either AresEditor or AresLauncher).

When running AresEditor, log messages can be seen in the ```Logs``` editor window.

**Formatting:**

See [spdlog's documentation](https://github.com/gabime/spdlog#basic-usage) for different formatting options.

| Method | Description |
| --- | --- |
| static void Log | Log a normal message |
| static void Info | Log an info (green) message |
| static void Warn | Log a warning (yellow) message |
| static void Error | Log an error (red) message |
| static void Critical | Log a critical (red background) message |
<hr>
