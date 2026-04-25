cmake_minimum_required(VERSION 3.10)
project(HakEngine)

# Find the package (Nix puts this in the CMAKE_PREFIX_PATH automatically)
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(HakEngine src/main.cpp)

target_link_libraries(HakEngine 
    PRIVATE 
        glfw 
        OpenGL::GL
)
