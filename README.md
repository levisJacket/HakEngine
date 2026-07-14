
# HakEngine

a minimal game engine made with C++.

### Requirements

cmake 3.10

glfw 3.3

OpenGL

GLM

### Design

1. Engine Loop
- Initialization: GLFW, GLAD, Jolt Setup, Asset Preload
- Update : Delta time -> Physics Step -> Render Step
- Shutdown: Resource cleanup, Jolt termination, GLFW termination

2. Core Data Structures

Entity
- ID: Unique unsigned int
- Transform: Position vec3, Rotation quat, Scale float

Mesh
- GPU Buffers: VAO, VBO, EBO handles
- Materials: Texture ID

3. Core Systems

EntityManager
- Entity creation, ID lookup, component mapping
- Flat array

PhysicsManager (aka Jolt Wrapper)
- Timestep ticking, transform synchronization
- BodyInterface -> Entity Transform

Renderer
- Pass 2D/3D draws, bind active shaders, lighting calculations

4. Conventions & Standards
- Matrix Notation: Column-Vector order, Right-to-Left multiplication
- Coordinate System: Left-handed, Y-Up
