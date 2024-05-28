cmake_minimum_required( VERSION 2.8.12 )

project( RCCpp-DearImGui-GLFW-example )

find_package( OpenGL REQUIRED )

include_directories( "glfw/include" )

include_directories("imgui")
include_directories("imgui/examples")
include_directories("RuntimeCompiledCPlusPlus/Aurora/RuntimeObjectSystem")
include_directories("RuntimeCompiledCPlusPlus/Aurora/RuntimeCompiler")
include_directories( ${OPENGL_INCLUDE_DIRS} )

set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_BUILD_TESTS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_BUILD_INSTALL OFF CACHE BOOL  "GLFW lib only" )
set( BUILD_EXAMPLES OFF CACHE BOOL  "RCCpp libsonly" )

add_subdirectory( glfw )
add_subdirectory( RuntimeCompiledCPlusPlus/Aurora )

if( UNIX )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
endif()

if( APPLE )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++" )
endif()

if( WIN32 )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" )
endif()

set( RCCPP-DEARIMGUI-GLFW-EXAMPLE-SRC
     imgui/imgui.h
     imgui/imgui.cpp
     imgui/imgui_internal.h
     imgui/imgui_demo.cpp
     imgui/imgui_draw.cpp
     imgui/imgui_widgets.cpp
     imgui/imconfig.h
     imgui/examples/imgui_impl_glfw.h
     imgui/examples/imgui_impl_glfw.cpp
     imgui/examples/imgui_impl_opengl2.h
     imgui/examples/imgui_impl_opengl2.cpp
     main.cpp
     StdioLogSystem.h
     StdioLogSystem.cpp
     RCCppMainLoop.h
     RCCppMainLoop.cpp
     SystemTable.h
     )

add_executable( RCCpp-DearImGui-GLFW-example ${RCCPP-DEARIMGUI-GLFW-EXAMPLE-SRC} )
target_link_libraries( RCCpp-DearImGui-GLFW-example ${OPENGL_LIBRARIES} glfw ${GLFW_LIBRARIES} RuntimeCompiler RuntimeObjectSystem )
if( MSVC )
    if( ${CMAKE_VERSION} VERSION_LESS "3.6.0" )
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'RCCpp-DearImGui-GLFW-example' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT RCCpp-DearImGui-GLFW-example )
    endif()
endif()

		if(MSVC)
			set_target_properties(RCCpp-DearImGui-GLFW-example PROPERTIES COMPILE_FLAGS "/FC /utf-8")
		else()
			add_compile_options("-DCOMPILE_PATH=\"\\\"$(PWD)\\\"\"")
		endif()

