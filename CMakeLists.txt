cmake_minimum_required(VERSION 3.10)
project(HakEngine)

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
    src/Physics.cpp	src/Physics.hpp
    src/CollisionManager.cpp 	src/CollisionManager.hpp
    src/Collider.cpp 	src/Collider.hpp
    src/Contact.hpp

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
)
