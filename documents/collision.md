
Two types of colliders : 

With Physics; for moving objects
Without Physics; for static objects

Resolving collision(contact) :

calculate seperating velocity between colliders.

resolve collisions, starting from the lowest seperating velocity.
    if collide:
        - change velocity based on restitution
        - resolve interpenetration


