add_compile_options(-msse4.1 -mno-avx -mno-avx2 -mno-fma)
add_compile_options(-fno-omit-frame-pointer)

cmake_minimum_required(VERSION 3.10)
project(HakEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -msse4.1 -mno-avx -mno-avx2 -mno-fma")
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -fno-omit-frame-pointer -msse4.1 -mno-avx -mno-avx2 -mno-fma")
set(CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_INIT   "${CMAKE_C_FLAGS}"   CACHE STRING "" FORCE)
set(JPH_ENABLE_AVX2 OFF CACHE BOOL "" FORCE)
set(JPH_ENABLE_AVX  OFF CACHE BOOL "" FORCE)
set(JPH_ENABLE_FMA  OFF CACHE BOOL "" FORCE)

# Force Jolt Physics options to match our Celeron N4020 CPU (No AVX/AVX2/F16C/FMA!)
set(USE_AVX OFF CACHE BOOL "Disable AVX" FORCE)
set(USE_AVX2 OFF CACHE BOOL "Disable AVX2" FORCE)
set(USE_AVX512 OFF CACHE BOOL "Disable AVX512" FORCE)
set(USE_F16C OFF CACHE BOOL "Disable F16C" FORCE)
set(USE_FMADD OFF CACHE BOOL "Disable FMADD" FORCE)

include(FetchContent)
FetchContent_Declare(
    JoltPhysics
    GIT_REPOSITORY https://github.com/jrouwe/JoltPhysics.git
    GIT_TAG        v5.2.0          # Or latest stable tag
    GIT_SHALLOW    TRUE
    SOURCE_SUBDIR  Build           # <--- CRITICAL: Jolt's CMakeLists.txt is inside Build/ folder
)

FetchContent_MakeAvailable(JoltPhysics)


find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
#find_package(GLAD REQUIRED)

set(PROJECT_SOURCES
    src/main.cpp
    src/glad.c

    src/Engine.cpp 	src/Engine.hpp

    src/AssetLoader.cpp src/AssetLoader.hpp
    src/Mesh.cpp   	src/Mesh.hpp
    src/stb_image.h

    src/EntityManager.cpp	src/EntityManager.hpp
    src/Entity.cpp 	src/Entity.hpp
    src/Transform.cpp 	src/Transform.hpp

    src/PhysicsManager.cpp  	src/PhysicsManager.hpp

    src/Renderer.cpp 	src/Renderer.hpp
    src/Shader.cpp 	src/Shader.hpp
    src/Light.cpp 	src/Light.hpp

    src/Camera.cpp 	src/Camera.hpp
)

add_executable(HakEngine ${PROJECT_SOURCES})

target_link_libraries(HakEngine 
    PRIVATE
        glfw 
        OpenGL::GL
	Jolt
)
