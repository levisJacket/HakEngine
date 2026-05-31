cmake_minimum_required(VERSION 3.10)
project(HakEngine)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
#find_package(GLAD REQUIRED)

set(PROJECT_SOURCES
    src/main.cpp
    src/glad.c

    src/AssetLoader.cpp
    src/AssetLoader.hpp

    src/Shader.cpp
    src/Shader.hpp

    src/Mesh.cpp  
    src/Mesh.hpp

    src/Entity.cpp
    src/Entity.hpp
)

add_executable(HakEngine ${PROJECT_SOURCES})

target_link_libraries(HakEngine 
    PRIVATE
        glfw 
        OpenGL::GL
)
