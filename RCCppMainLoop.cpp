#include "ObjectInterfacePerModule.h"
#include "IObject.h"
#include "RCCppMainLoop.h"
#include "SystemTable.h"

#include "imgui.h"

// add imgui source dependencies
// an alternative is to put imgui into a library and use RuntimeLinkLibrary
#include "RuntimeSourceDependency.h"
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE( "imgui/imgui", ".cpp" );
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE( "imgui/imgui_widgets", ".cpp" );
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE( "imgui/imgui_draw", ".cpp" );
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE( "imgui/imgui_demo", ".cpp" );

// RCC++ uses interface Id's to distinguish between different classes
// here we have only one, so we don't need a header for this enum and put it in the same
// source code file as the rest of the code
enum InterfaceIDEnumConsoleExample
{
    IID_IRCCPP_MAIN_LOOP = IID_ENDInterfaceID, // IID_ENDInterfaceID from IObject.h InterfaceIDEnum

    IID_ENDInterfaceIDEnumConsoleExample
};

struct RCCppMainLoop : RCCppMainLoopI, TInterface<IID_IRCCPP_MAIN_LOOP,IObject>
{
    RCCppMainLoop()
    {
        PerModuleInterface::g_pSystemTable->pRCCppMainLoopI = this;
    }

    void MainLoop() override
    {
        ImGui::SetCurrentContext( PerModuleInterface::g_pSystemTable->pImContext );

        ImGui::SetNextWindowPos(ImVec2(50,400), ImGuiCond_Appearing );
        ImGui::SetNextWindowSize(ImVec2(0,0), ImGuiCond_Always );
        ImGui::Begin("RCCppMainLoop Window" );
        ImGui::Text("You can change Window's code at runtime!");
        ImGui::End();
    }
};

REGISTERSINGLETON(RCCppMainLoop,true);
