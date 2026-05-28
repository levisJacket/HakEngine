cmake_minimum_required(VERSION 3.10)
project(HakEngine)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
#find_package(GLAD REQUIRED)


add_executable(HakEngine src/main.cpp src/glad.c src/AssetLoader.cpp src/AssetLoader.h src/Shader.cpp src/Shader.h)

target_link_libraries(HakEngine 
    PRIVATE
        glfw 
        OpenGL::GL
)
