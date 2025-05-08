#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>


struct CollisionComponent
{
    std::vector<int> collisionWithComponents;
};

#endif //COLLISION_COMPONENT_H