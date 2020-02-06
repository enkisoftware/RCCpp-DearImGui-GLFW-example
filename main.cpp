#include <stdlib.h>

#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"

#include <GLFW/glfw3.h>

#include "RuntimeObjectSystem.h"

// headers from our example 
#include "StdioLogSystem.h"

// RCC++ Data
static IRuntimeObjectSystem*	g_pRuntimeObjectSystem;
static StdioLogSystem           g_Logger;

bool RCCppInit();
void RCCppCleanup();
void RCCppUpdate();

int main( int argc, const char * argv[] )
{
    if (!glfwInit())
        exit(1);

    // Initialize RCC++
    RCCppInit();

    GLFWwindow* window = glfwCreateWindow(1280, 720, "CMake RCC++ Dear ImGui starter", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();

    // Setup style
    ImGui::StyleColorsDark();

    ImVec4 clear_color = ImColor(114, 144, 154);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Update RCC++
        RCCppUpdate();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        static bool show_demo_window = true;
        if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

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
    g_pRuntimeObjectSystem = new RuntimeObjectSystem;
	if( !g_pRuntimeObjectSystem->Initialise(&g_Logger, NULL) )
    {
        g_pRuntimeObjectSystem = NULL;
        return false;
    }
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