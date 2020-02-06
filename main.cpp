#include <stdlib.h>

// imgui headers
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"

#include <GLFW/glfw3.h>

// RCC++ headers
#include "RuntimeObjectSystem.h"

// headers from our example 
#include "StdioLogSystem.h"
#include "SystemTable.h"
#include "RCCppMainLoop.h"

// RCC++ Data
static IRuntimeObjectSystem*	g_pRuntimeObjectSystem;
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

    g_pRuntimeObjectSystem = new RuntimeObjectSystem;
    if( !g_pRuntimeObjectSystem->Initialise(&g_Logger, &g_SystemTable) )
    {
        delete g_pRuntimeObjectSystem;
        g_pRuntimeObjectSystem = 0;
        return false;
    }

    g_pRuntimeObjectSystem->CleanObjectFiles();

    // ensure include directories are set - use location of this file as starting point
    FileSystemUtils::Path basePath = g_pRuntimeObjectSystem->FindFile( __FILE__ ).ParentPath();
    FileSystemUtils::Path imguiIncludeDir = basePath / "imgui";
    g_pRuntimeObjectSystem->AddIncludeDir( imguiIncludeDir.c_str() );

    return true;
}

void RCCppCleanup()
{
	delete g_pRuntimeObjectSystem;
}

void RCCppUpdate()
{
    //check status of any compile
    if( g_pRuntimeObjectSystem->GetIsCompiledComplete() )
    {
        // load module when compile complete
        g_pRuntimeObjectSystem->LoadCompiledModule();
    }

    if( !g_pRuntimeObjectSystem->GetIsCompiling() )
    {
        float deltaTime = 1.0f / ImGui::GetIO().Framerate;
        g_pRuntimeObjectSystem->GetFileChangeNotifier()->Update( deltaTime );
    }
}