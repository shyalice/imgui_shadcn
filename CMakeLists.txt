cmake_minimum_required(VERSION 4.0)
project(shadcn_imgui LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-ffast-math -ftime-trace -O3 -w -Wno-error=format-security -fvisibility=hidden -Wno-error -Wno-narrowing -Wall -fexceptions")
set(CMAKE_C_FLAGS   "-ftime-trace -O3 -w -Wno-error=format-security -fvisibility=hidden -fexceptions")

include(FetchContent)

FetchContent_Declare(
        ixwebsocket
        GIT_REPOSITORY https://github.com/machinezone/IXWebSocket.git
        GIT_TAG v11.4.6
)
FetchContent_MakeAvailable(ixwebsocket)

find_package(OpenGL REQUIRED)
find_package(CURL REQUIRED)

add_subdirectory(shadcn)

find_package(glfw3 CONFIG REQUIRED)

add_library(imgui STATIC
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_demo.cpp
        imgui/backends/imgui_impl_opengl3.cpp
        imgui/backends/imgui_impl_opengl3_loader.h
        imgui/backends/imgui_impl_opengl3.h
        imgui/backends/imgui_impl_glfw.cpp
        examples/login_screen.cpp
        examples/login_screen.hpp
)

target_include_directories(imgui PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/imgui
        ${CMAKE_CURRENT_LIST_DIR}/imgui/backends
        ${CMAKE_CURRENT_LIST_DIR}/glad/include
)

target_link_libraries(imgui PUBLIC glfw)

add_executable(shadcn_imgui
        main.cpp

        glad/include/glad/glad.h
        glad/include/KHR/khrplatform.h
        glad/src/glad.c
)

target_include_directories(shadcn_imgui PUBLIC
        json
)

target_link_libraries(shadcn_imgui PRIVATE
        imgui
        shadcn
        OpenGL::GL
        ixwebsocket
        CURL::libcurl
)

target_link_libraries(shadcn PRIVATE imgui)
target_link_libraries(shadcn_imgui PRIVATE imgui shadcn)

if(APPLE)
    target_link_libraries(shadcn_imgui PRIVATE
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreVideo"
    )
endif()
