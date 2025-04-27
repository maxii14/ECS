#ifndef BOX_COLLIDER_COMPONENT_H
#define BOX_COLLIDER_COMPONENT_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>


struct BoxColliderComponent
{
    float _xSize;
    float _ySize;
    sf::Vector2f _refPoint;

    BoxColliderComponent(float xSize, float ySize, sf::Vector2f point):
        _xSize(xSize), _ySize(ySize), _refPoint(point){}

    BoxColliderComponent():
        _xSize(5.0f), _ySize(5.0f), _refPoint({1.0f, 1.0f}){}
};

#endif //BOX_COLLIDER_COMPONENT_H