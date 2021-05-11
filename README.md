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

## Building The Engine
<hr>

1 - Update the install directories of all the dependences at the top of ```premake5.lua```.

2 - Run ```GenerateProject.bat```.

3 - Build the ```AresEditor``` project.

4 - All the required files and libraries for the engine will be in ```Builds\Release\AresEditor\``` (or ```Builds\Debug\AresEditor\``` depending on the configuration you build)


## Scripting
<hr>
Coming soon...