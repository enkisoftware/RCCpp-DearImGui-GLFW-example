Support our work through [GitHub Sponsors](https://github.com/sponsors/dougbinks) or [Patreon](https://www.patreon.com/enkisoftware)

[<img src="https://img.shields.io/static/v1?logo=github&label=Github&message=Sponsor&color=#ea4aaa" width="200"/>](https://github.com/sponsors/dougbinks)    [<img src="https://c5.patreon.com/external/logo/become_a_patron_button@2x.png" alt="Become a Patron" width="150"/>](https://www.patreon.com/enkisoftware)


# RCC++ Dear ImGui GLFW example

This project adds Runtime Compiled C++ to the Dear ImGui example using the GLFW and OpenGL backend. This enables us to edit the code at runtime and see the results live, without recompiling and restarting the project. 

This is a cross platform project using CMake.

Runtime-Compiled C++ (RCC++) is a way to reliably make major changes to C++ code at runtime and see the results immediately. It's aimed at games development but could be useful in any industry where turnaround times are a bottleneck.

[github.com/RuntimeCompiledCPlusPlus/RuntimeCompiledCPlusPlus](https://github.com/RuntimeCompiledCPlusPlus/RuntimeCompiledCPlusPlus)

RCC++ is primarily designed to shorten iteration times in development - developers can build their project, run it, make changes during runtime and see the results in a few seconds.

![Short teaser of Runtime Compiled C++ Dear ImGui example running on Linux](https://github.com/juliettef/Media/blob/master/RCCpp-DearImGui-example.gif)

Note - you can also find a similar Windows-only example in the devlog post [Runtime Compiled C++ Dear ImGui and DirectX11 Tutorial](https://www.enkisoftware.com/devlogpost-20200202-1-Runtime-Compiled-C++-Dear-ImGui-and-DirectX11-Tutorial).

## Getting the code

The easiest way to get hold of the starter code is to run the following command using a shell you can run git from:

```
git clone --recursive https://github.com/juliettef/RCCpp-DearImGui-GLFW-example
```

If you are on Windows you can download git from [git-scm.com/download/win](https://git-scm.com/download/win) and use the right click menu in Windows File Explorer to "Git Bash here" and then run git commands.

This will create the directory _RCCpp-DearImGui-GLFW-example_ and get the latest source code, using the ```--recursive``` option to download the RuntimeCompiledCPlusPlus, Dear ImGui and GLFW code, which have been included in the tutorial repository as submodules. If you want to run further git commands from the command line you'll need to cd into the directory:

```
cd RCCpp-DearImGui-GLFW-example
```

Alternatively you can use a git GUI program such as [Fork](https://git-fork.com/) to get the code. Most of these will automatically download the git submodules.

If you download the code from GitHub via the "Download ZIP" approach, you'll also need to download the RuntimeCompiledCPlusPlus, Dear ImGui and GLFW into the _RuntimeCompiledCPlusPlus_, _imgui_ and _glfw_ directories. The correct version can be found by clicking on the _RuntimeCompiledCPlusPlus_, _imgui_ and _glfw_ folders you see on the [front page of the _RCCpp-DearImGui-GLFW-example_ GitHub repository](https://github.com/juliettef/RCCpp-DearImGui-GLFW-example).

## Using CMake to create the project

From a command prompt in the `RCCpp-DearImGui-GLFW-example` directory:
1. `mkdir build`
1. `cd build`
1. `cmake ..`
1. Either run `make all` or for Visual Studio open `RCCpp-DearImGui-GLFW-example.sln`
    
The _RCCpp-DearImGui-GLFW-example_ Window should open.
