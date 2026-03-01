cmake_minimum_required(VERSION 4.0)

add_library(shadcn STATIC
        include/shadcn/styles/styles.hpp
        src/styles/styles.cpp
        include/shadcn/color/color.hpp
        src/elem/checkbox.cpp
        include/shadcn/elem/checkbox.hpp
        include/shadcn/elem/elem.hpp
        src/elem/elem.cpp
        src/elem/button.cpp
        include/shadcn/elem/button.hpp
        src/elem/input_text.cpp
        include/shadcn/elem/input_text.hpp
        src/elem/text.cpp
        include/shadcn/elem/text.hpp
        src/elem/card.cpp
        include/shadcn/elem/card.hpp
        include/shadcn/elem/toggle.hpp
        src/elem/toggle.cpp)

file(GLOB_RECURSE SHADCN_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/src/*.c"
)

file(GLOB_RECURSE SHADCN_ROOT_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/*.c"
)

target_sources(shadcn PRIVATE
        ${SHADCN_SOURCES}
        ${SHADCN_ROOT_SOURCES}
)

target_include_directories(shadcn
        PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}"
        "${CMAKE_CURRENT_LIST_DIR}/include"
        "${CMAKE_CURRENT_LIST_DIR}/include/shadcn"
        PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/src"
)
