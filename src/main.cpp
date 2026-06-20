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


    engine.getEntity(sphere1)->setPosition(vec3(0.0f, 0.0f, 10.0f));
    engine.getEntity(sphere1)->setScale(2.0f);

    engine.getEntity(sphere2)->setPosition(vec3(15.0f, 0.0f, 10.0f));
    engine.getEntity(sphere2)->setScale(2.0f);

    engine.getEntity(floor)->setPosition(vec3(0.0f, -1.0f, 0.0f));
    engine.getEntity(floor)->setScale(30.0f);

    engine.addPhysics(sphere1, 1.0f);
    engine.addCollider(sphere1);
    engine.addPhysics(sphere2, 5.0f);
    engine.addCollider(sphere2);

    engine.addImpulse(sphere1, vec3(1.0f, 15.0f, 0.0f));
    engine.addImpulse(sphere2, vec3(-20.0f, 30.0f, 0.0f));

    engine.addLight(vec3(0, 3, 0), vec3(1, 1, 1));

    engine.run();

    return 0;
}
