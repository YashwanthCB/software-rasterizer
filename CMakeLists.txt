cmake_minimum_required(VERSION 4.1)
project(rasteryzen)

find_package(X11 REQUIRED)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(rasteryzen main.cpp
        TGAImage.cpp
        TGAImage.h
        RendererWireframe.cpp
        RendererWireframe.h
        Utils.cpp
        Utils.h
        Rasterizer.cpp
        Rasterizer.h
        DisplayWindow.cpp
        DisplayWindow.h
)

target_link_libraries(rasteryzen PRIVATE X11::X11)