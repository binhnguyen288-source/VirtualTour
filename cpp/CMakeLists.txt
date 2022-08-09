cmake_minimum_required(VERSION 3.22)
project(cubemap)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-O3 -ffast-math)

add_link_options(
    -O3 -ffast-math
    -sEXPORTED_FUNCTIONS=_malloc,_free,_jsCubeMap,_viewerQuery
    -sSINGLE_FILE -sALLOW_MEMORY_GROWTH
)


add_executable(viewer main.cpp)