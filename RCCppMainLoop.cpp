#include "ObjectInterfacePerModule.h"
#include "IObject.h"
#include "RCCppMainLoop.h"
#include "SystemTable.h"
#include "ISimpleSerializer.h"
#include "IRuntimeObjectSystem.h"

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
    bool show_demo_window = true;

    // data for compiling window
    static constexpr double SHOW_AFTER_COMPILE_TIME = 3.0f;
    double compileStartTime    = -SHOW_AFTER_COMPILE_TIME;
    double compileEndTime      = -SHOW_AFTER_COMPILE_TIME;

    RCCppMainLoop()
    {
        PerModuleInterface::g_pSystemTable->pRCCppMainLoopI = this;
    }

    void Init( bool isFirstInit ) override
    {
        // If you want to do any initialization which is expensive and done after state
        // has been serialized you can do this here.

        if( isFirstInit )
        {
            // do any init needed to be done only once here, isFirstInit only set
            // when object is first constructed at program start.
        }
        // can do any initialization you might want to change here.
    }

    void Serialize( ISimpleSerializer *pSerializer ) override
    {
        SERIALIZE( show_demo_window );
        SERIALIZE( compileStartTime );
        SERIALIZE( compileEndTime );
    }

    void MainLoop() override
    {
        ImGui::SetCurrentContext( PerModuleInterface::g_pSystemTable->pImContext );

        ImGui::SetNextWindowPos(ImVec2(50,400), ImGuiCond_Appearing );
        ImGui::SetNextWindowSize(ImVec2(0,0), ImGuiCond_Always );
        ImGui::Begin("RCCppMainLoop Window" );
        ImGui::Text("You can change Window's code at runtime!");
        ImGui::End();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

        // Show compiling info
        double time = ImGui::GetTime();
        bool bCompiling = g_pSys->pRuntimeObjectSystem->GetIsCompiling();
        double timeSinceLastCompile = time - compileEndTime;
        if( bCompiling  || timeSinceLastCompile < SHOW_AFTER_COMPILE_TIME )
        {
            if( bCompiling )
            {
                if( timeSinceLastCompile > SHOW_AFTER_COMPILE_TIME )
                {
                    compileStartTime = time;
                }
                compileEndTime = time; // ensure always updated
            }
            bool bCompileOk = g_pSys->pRuntimeObjectSystem->GetLastLoadModuleSuccess();

            ImVec4 windowBgCol = ImVec4(0.1f,0.4f,0.1f,1.0f);
            if( !bCompiling )
            {
                if( bCompileOk )
                {
                    windowBgCol = ImVec4(0.1f,0.7f,0.1f,1.0f);
                }
                else
                {
                    windowBgCol = ImVec4(0.7f,0.1f,0.1f,1.0f);
                }
            }
            ImGui::PushStyleColor(ImGuiCol_WindowBg,windowBgCol);

            ImVec2 sizeAppWindow = ImGui::GetIO().DisplaySize;
            ImGui::SetNextWindowPos(ImVec2( sizeAppWindow.x - 300, sizeAppWindow.y - 50), ImGuiCond_Always );
            ImGui::SetNextWindowSize(ImVec2(280,0), ImGuiCond_Always );
            ImGui::Begin("Compiling", NULL, ImGuiWindowFlags_NoTitleBar );
            if( bCompiling )
            {
                ImGui::Text("Compiling... time %.2fs", (float)(time - compileStartTime) );
            }
            else
            {
                if( bCompileOk )
                {
                    ImGui::Text("Compiling... time %.2fs. SUCCEED", (float)(compileEndTime - compileStartTime) );
                }
                else
                {
                    ImGui::Text("Compiling... time %.2fs. FAILED", (float)(compileEndTime - compileStartTime) );
                }
            }
            ImGui::End();
            ImGui::PopStyleColor();
        }
    }
};

REGISTERSINGLETON(RCCppMainLoop,true);
