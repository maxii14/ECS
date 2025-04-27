#ifndef CIRCLE_COLLIDER_COMPONENT_H
#define CIRCLE_COLLIDER_COMPONENT_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>


struct CircleColliderComponent
{
    float _radius;
    sf::Vector2f _refPoint;

    CircleColliderComponent(float radius, sf::Vector2f point):
        _radius(radius), _refPoint(point){}

    CircleColliderComponent():
        _radius(1.0f), _refPoint({1.0f, 1.0f}){}
};

#endif //CIRCLE_COLLIDER_COMPONENT_H