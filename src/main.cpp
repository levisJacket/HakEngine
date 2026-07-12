#include "Engine.hpp"

#include <iostream>
#include <vector>

using glm::vec3;

int main(void)
{
    Engine engine;
    engine.init();

    unsigned int sphere1 = engine.createEntity("sphere.stl");
    unsigned int sphere2 = engine.createEntity("sphere.stl");
    unsigned int floor = engine.createEntity("floor.stl");

    engine.getEntity(sphere1)->setPosition(vec3(-5.0f, 3.0f, 5.0f));
    engine.getEntity(sphere1)->setScale(1.0f);

    engine.getEntity(sphere2)->setPosition(vec3(5.0f, 3.0f, 5.0f));
    engine.getEntity(sphere2)->setScale(1.0f);

    engine.getEntity(floor)->setPosition(vec3(0.0f, 0.0f, 0.0f));
    engine.getEntity(floor)->setScale(30.0f);

    engine.addBody(sphere1,
	BodyInfo {
	    .mass = 1.0f,
	    .type = ColliderType::Sphere,
	    .radius = 0.5f
	}
    );
    engine.addBody(sphere2,
	BodyInfo {
	    .mass = 1.0f,
	    .type = ColliderType::Sphere,
	    .radius = 0.5f
	}
    );
    engine.addBody(floor,
	BodyInfo {
	    .mass = 0.0f,
	    .type = ColliderType::Cube,
	    .halfExtents = {30.0f, 0.5f, 30.0f}
	}
    );

    engine.addImpulse(sphere1, vec3(3, 10, 0));
    engine.addImpulse(sphere2, vec3(-1, 0, 0));

    engine.addLight(Light{
		.position = vec3(0, 3, 0),
		.color = vec3(1, 1, 1),
		.radius = 2000.0f,
		.intensity = 10.0f
	    }
    );

    engine.run();

    return 0;
}
