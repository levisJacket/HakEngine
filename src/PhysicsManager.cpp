#include "PhysicsManager.hpp"
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/PlaneShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <iostream>

// Jolt namespaces
using namespace JPH;

// Broadphase Layers
namespace Layers {
    static constexpr ObjectLayer NON_MOVING = 0;
    static constexpr ObjectLayer MOVING = 1;
    static constexpr ObjectLayer NUM_LAYERS = 2;
}

namespace BroadPhaseLayers {
    static constexpr BroadPhaseLayer NON_MOVING(0);
    static constexpr BroadPhaseLayer MOVING(1);
    static constexpr uint NUM_LAYERS = 2;
}

// BroadPhaseLayerInterface implementation
class BPLayerInterfaceImpl : public BroadPhaseLayerInterface {
public:
    BPLayerInterfaceImpl() {
        mObjectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
        mObjectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
    }

    virtual uint GetNumBroadPhaseLayers() const override {
        return BroadPhaseLayers::NUM_LAYERS;
    }

    virtual BroadPhaseLayer GetBroadPhaseLayer(ObjectLayer inLayer) const override {
        return mObjectToBroadPhase[inLayer];
    }

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
    virtual const char* GetBroadPhaseLayerName(BroadPhaseLayer inLayer) const override {
        switch ((BroadPhaseLayer::Type)inLayer) {
            case (BroadPhaseLayer::Type)BroadPhaseLayers::NON_MOVING: return "NON_MOVING";
            case (BroadPhaseLayer::Type)BroadPhaseLayers::MOVING: return "MOVING";
            default: return "INVALID";
        }
    }
#endif

private:
    BroadPhaseLayer mObjectToBroadPhase[Layers::NUM_LAYERS];
};

// ObjectLayerPairFilter implementation
class ObjectLayerPairFilterImpl : public ObjectLayerPairFilter {
public:
    virtual bool ShouldCollide(ObjectLayer inObject1, ObjectLayer inObject2) const override {
        switch (inObject1) {
            case Layers::NON_MOVING:
                return inObject2 == Layers::MOVING; // Static only collides with Moving
            case Layers::MOVING:
                return true; // Moving collides with everything
            default:
                return false;
        }
    }
};

// ObjectVsBroadPhaseLayerFilter implementation
class ObjectVsBroadPhaseLayerFilterImpl : public ObjectVsBroadPhaseLayerFilter {
public:
    virtual bool ShouldCollide(ObjectLayer inLayer1, BroadPhaseLayer inLayer2) const override {
        switch (inLayer1) {
            case Layers::NON_MOVING:
                return inLayer2 == BroadPhaseLayers::MOVING; // Static checks against Moving Broadphase
            case Layers::MOVING:
                return true; // Moving checks against all
            default:
                return false;
        }
    }
};

// Local instances of layers
static BPLayerInterfaceImpl broadPhaseLayerInterface;
static ObjectVsBroadPhaseLayerFilterImpl objectVsBroadPhaseLayerFilter;
static ObjectLayerPairFilterImpl objectLayerPairFilter;

PhysicsManager::PhysicsManager() : entityManager(nullptr) {}

PhysicsManager::PhysicsManager(EntityManager* entityManager) {
    this->entityManager = entityManager;
}

PhysicsManager::~PhysicsManager() {
    if (m_jobSystem) {
        delete m_jobSystem;
        m_jobSystem = nullptr;
    }
    if (m_tempAllocator) {
        delete m_tempAllocator;
        m_tempAllocator = nullptr;
    }
}

bool PhysicsManager::init() {
    // 1. Setup Jolt's dynamic allocation and static class registration
    RegisterDefaultAllocator();
    Factory::sInstance = new Factory();
    RegisterTypes();

    // 2. Allocate Jolt's temp memory stack (20 MB scratchpad)
    m_tempAllocator = new TempAllocatorImpl(20 * 1024 * 1024);

    // 3. Initialize multi-threaded job scheduler (using hardware concurrency minus 1)
    m_jobSystem = new JobSystemThreadPool(
        cMaxPhysicsJobs,
        cMaxPhysicsBarriers,
        std::max(1, (int)std::thread::hardware_concurrency() - 1)
    );

    // 4. Initialize physics system
    const uint maxBodies = 1024;
    const uint numBodyMutexes = 0; // 0 = automatic
    const uint maxBodyPairs = 1024;
    const uint maxContactConstraints = 1024;

    m_physicsSystem.Init(
        maxBodies,
        numBodyMutexes,
        maxBodyPairs,
        maxContactConstraints,
        broadPhaseLayerInterface,
        objectVsBroadPhaseLayerFilter,
        objectLayerPairFilter
    );

    // 5. Store BodyInterface pointer for faster lookups
    m_bodyInterface = &m_physicsSystem.GetBodyInterface();

    return true;
}

bool PhysicsManager::addBody(unsigned int entityID, BodyInfo info) {
    if (!m_bodyInterface) return false;

    Entity* entity = entityManager->getEntity(entityID);
    if (!entity) return false;

    glm::vec3 entityPos = entity->getPosition();
    RVec3 startPos(entityPos.x, entityPos.y, entityPos.z);
    
    ShapeRefC shape;

    // Create shapes depending on input parameters
    if (info.type == ColliderType::Sphere) {
        SphereShapeSettings shapeSettings(info.radius);
        Shape::ShapeResult result = shapeSettings.Create();
        if (result.IsValid()) {
            shape = result.Get();
        }
    } 
    else if (info.type == ColliderType::Plane) {
        // Jolt Plane representation: a static box is extremely stable for ground levels!
        // If we want an infinite plane, PlaneShape exists.
        PlaneShapeSettings shapeSettings(Plane(Vec3(info.normal.x, info.normal.y, info.normal.z), info.distance));
        Shape::ShapeResult result = shapeSettings.Create();
        if (result.IsValid()) {
            shape = result.Get();
        }
    } 
    else if (info.type == ColliderType::Cube) {
        BoxShapeSettings shapeSettings(Vec3(info.halfExtents.x, info.halfExtents.y, info.halfExtents.z));
        Shape::ShapeResult result = shapeSettings.Create();
        if (result.IsValid()) {
            shape = result.Get();
        }
    }

    if (!shape) {
        std::cerr << "Failed to create Jolt shape for entity " << entityID << std::endl;
        return false;
    }

    // Determine motion type (static if mass <= 0 or 0, dynamic otherwise)
    EMotionType motionType = (info.mass <= 0.0f) ? EMotionType::Static : EMotionType::Dynamic;
    ObjectLayer layer = (info.mass <= 0.0f) ? Layers::NON_MOVING : Layers::MOVING;

    BodyCreationSettings creationSettings(
        shape,
        startPos,
        Quat::sIdentity(),
        motionType,
        layer
    );

    if (motionType == EMotionType::Dynamic) {
        creationSettings.mMassPropertiesOverride.mMass = info.mass;
        creationSettings.mOverrideMassProperties = EOverrideMassProperties::CalculateInertia;
    }

    Body* body = m_bodyInterface->CreateBody(creationSettings);
    if (!body) {
        std::cerr << "Failed to create Jolt body for entity " << entityID << std::endl;
        return false;
    }

    m_bodyInterface->AddBody(body->GetID(), EActivation::Activate);
    m_entityToBodyMap[entityID] = body->GetID();

    return true;
}

void PhysicsManager::update(float timeStep) {
    if (!m_bodyInterface) return;
    const float FIXED_TIMESTEP = 1.0f / 30.0f;

    timeAccum += timeStep;
    while (timeAccum >= FIXED_TIMESTEP){
	m_physicsSystem.Update(
	    FIXED_TIMESTEP,
	    1,
	    m_tempAllocator,
	    m_jobSystem
	);
	timeAccum -= FIXED_TIMESTEP;
    }

    // Keep shapes in sync
    syncTransforms();
}

void PhysicsManager::addImpulse(unsigned int entityID, glm::vec3 force) {
    auto it = m_entityToBodyMap.find(entityID);
    if (it != m_entityToBodyMap.end()) {
        m_bodyInterface->AddImpulse(it->second, Vec3(force.x, force.y, force.z));
    }
}

void PhysicsManager::addTorque(unsigned int entityID, glm::vec3 torque) {
    auto it = m_entityToBodyMap.find(entityID);
    if (it != m_entityToBodyMap.end()) {
        m_bodyInterface->AddTorque(it->second, Vec3(torque.x, torque.y, torque.z));
    }
}

void PhysicsManager::syncTransforms() {
    for (const auto& [entityID, bodyID] : m_entityToBodyMap) {
        RVec3 position = m_bodyInterface->GetPosition(bodyID);
        Quat rotation = m_bodyInterface->GetRotation(bodyID);

        glm::vec3 glmPos(position.GetX(), position.GetY(), position.GetZ());
        glm::quat glmRot(rotation.GetW(), rotation.GetX(), rotation.GetY(), rotation.GetZ());

        Entity* entity = entityManager->getEntity(entityID);
        entity->setPosition(glmPos);
        entity->setRotation(glmRot); // Sync spin physics!
    }
}
