#include <stdlib.h>

// imgui headers
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"

// RCC++ headers
#include "RuntimeObjectSystem.h"

// headers from our example 
#include "StdioLogSystem.h"
#include "SystemTable.h"
#include "RCCppMainLoop.h"

#include <GLFW/glfw3.h>

// RCC++ Data
static StdioLogSystem           g_Logger;
static SystemTable              g_SystemTable;

bool RCCppInit();
void RCCppCleanup();
void RCCppUpdate();

int main( int argc, const char * argv[] )
{
    if (!glfwInit())
        exit(1);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "CMake RCC++ Dear ImGui starter", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();

    // Initialize RCC++
    RCCppInit();

    // Setup style
    ImGui::StyleColorsDark();

    ImVec4 clear_color = ImColor(114, 144, 154);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Update RCC++
        RCCppUpdate();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Call the function in our RCC++ class
        g_SystemTable.pRCCppMainLoopI->MainLoop();

        // Rendering
        {
            glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui::Render();
            ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);
        }
    }

    // Cleanup
    RCCppCleanup();
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}

bool RCCppInit()
{
    g_SystemTable.pImContext = ImGui::GetCurrentContext();

    g_SystemTable.pRuntimeObjectSystem = new RuntimeObjectSystem;
    if( !g_SystemTable.pRuntimeObjectSystem->Initialise(&g_Logger, &g_SystemTable) )
    {
        delete g_SystemTable.pRuntimeObjectSystem;
        g_SystemTable.pRuntimeObjectSystem = 0;
        return false;
    }

    g_SystemTable.pRuntimeObjectSystem->CleanObjectFiles();

    // ensure include directories are set - use location of this file as starting point
    FileSystemUtils::Path basePath = g_SystemTable.pRuntimeObjectSystem->FindFile( __FILE__ ).ParentPath();
    FileSystemUtils::Path imguiIncludeDir = basePath / "imgui";
    g_SystemTable.pRuntimeObjectSystem->AddIncludeDir( imguiIncludeDir.c_str() );

    return true;
}

void RCCppCleanup()
{
	delete g_SystemTable.pRuntimeObjectSystem;
}

void RCCppUpdate()
{
    //check status of any compile
    if( g_SystemTable.pRuntimeObjectSystem->GetIsCompiledComplete() )
    {
        // load module when compile complete
        g_SystemTable.pRuntimeObjectSystem->LoadCompiledModule();
    }

    if( !g_SystemTable.pRuntimeObjectSystem->GetIsCompiling() )
    {
        float deltaTime = 1.0f / ImGui::GetIO().Framerate;
        g_SystemTable.pRuntimeObjectSystem->GetFileChangeNotifier()->Update( deltaTime );
    }
}