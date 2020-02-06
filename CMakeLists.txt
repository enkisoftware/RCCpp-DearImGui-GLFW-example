cmake_minimum_required( VERSION 2.8 )

project( CMake-RCCpp-DearImGui-starter )

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
		SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++" )
endif()

set( CMAKE-RCCPP-DEARIMGUI-STARTER-SRC
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
     RCCppMainLoop.cpp
     )
	 
add_executable( CMake-RCCpp-DearImGui-starter ${CMAKE-RCCPP-DEARIMGUI-STARTER-SRC} )
target_link_libraries( CMake-RCCpp-DearImGui-starter ${OPENGL_LIBRARIES} glfw ${GLFW_LIBRARIES} RuntimeCompiler RuntimeObjectSystem )