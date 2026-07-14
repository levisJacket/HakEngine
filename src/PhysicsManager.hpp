#pragma once

#include "EntityManager.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <unordered_map>

#include <Jolt/Jolt.h>
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/Body/BodyID.h>

enum class ColliderType { Sphere, Plane, Cube };

struct BodyInfo {
    float mass = 0.0f;   
    ColliderType type;
    float radius = 1.0f;
    glm::vec3 normal = {0.0f, 1.0f, 0.0f};
    float distance = 0.0f;
    glm::vec3 halfExtents = {1.0f, 1.0f, 1.0f};
};

class PhysicsManager {
private:
    float timeAccum = 0.0f;
    EntityManager* entityManager;
    
    // Jolt instances
    JPH::TempAllocatorImpl* m_tempAllocator = nullptr;
    JPH::JobSystemThreadPool* m_jobSystem = nullptr;
    JPH::PhysicsSystem m_physicsSystem;
    JPH::BodyInterface* m_bodyInterface = nullptr;

    // Maps Entity IDs to Jolt's Body IDs
    std::unordered_map<unsigned int, JPH::BodyID> m_entityToBodyMap;

public:
    PhysicsManager();
    PhysicsManager(EntityManager* entityManager);
    ~PhysicsManager();

    bool init();
    void update(float timeStep);
    
    bool addBody(unsigned int entityID, BodyInfo info);
    
    void addImpulse(unsigned int entityID, glm::vec3 impulse);
    void addTorque(unsigned int entityID, glm::vec3 torque); // NEW: For object rotation physics!
    
    void syncTransforms();
};
