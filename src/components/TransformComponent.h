#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

struct TransformComponent {
    sf::Vector2f position;
    sf::Vector2f speed;
    sf::Angle rotationSpeed;
    bool canManuallyRotate;

    TransformComponent(
        sf::Vector2f pos,
        sf::Vector2f sp,
        sf::Angle rSpeed,
        bool canRotate
    ) : position(pos), speed(sp), rotationSpeed(rSpeed), canManuallyRotate(canRotate){}
    TransformComponent(){}
};

#endif //TRANSFORM_COMPONENT_H