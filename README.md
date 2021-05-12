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
