#include "Engine.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <chrono>

using glm::vec3;

int main(void)
{
    Engine engine;
    engine.init();

    unsigned int sphere1 = engine.createEntity("sphere.stl");
    unsigned int sphere2 = engine.createEntity("sphere.stl");
    unsigned int floor = engine.createEntity("floor.stl");

    engine.getEntity(sphere1)->setPosition(vec3(-5.0f, 0.0f, 5.0f));
    engine.getEntity(sphere1)->setScale(1.0f);

    engine.getEntity(sphere2)->setPosition(vec3(5.0f, 0.0f, 5.0f));
    engine.getEntity(sphere2)->setScale(1.0f);

    engine.getEntity(floor)->setPosition(vec3(0.0f, 0.0f, 0.0f));
    engine.getEntity(floor)->setScale(30.0f);

    engine.addPhysics(sphere1, 1.0f);
    engine.addPhysics(sphere2, 1.0f);

    ColliderInfo A; A.type = ColliderType::Sphere; A.radius = 1.0f;
    ColliderInfo B; B.type = ColliderType::Sphere; B.radius = 1.0f;
    ColliderInfo C; C.type = ColliderType::Plane; C.normal = vec3(0, 1, 0); C.distance = 0;

    engine.addCollider(sphere1, A);
    engine.addCollider(sphere2, B);
    engine.addCollider(floor, C);

    engine.addImpulse(sphere1, vec3(1, 10, 0));
    engine.addImpulse(sphere2, vec3(-1, 0, 0));

    engine.addLight(vec3(0, 3, 0), vec3(1, 1, 1));

    engine.run();

    return 0;
}
