#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>


struct CollisionComponent
{
    float _xSize;
    float _ySize;
    sf::Vector2f _leftTop;

    CollisionComponent(float xSize, float ySize, sf::Vector2f point):
        _xSize(xSize), _ySize(ySize), _leftTop(point){}

    CollisionComponent():
        _xSize(5.0f), _ySize(5.0f), _leftTop({1.0f, 1.0f}){}
};

#endif //COLLISION_COMPONENT_H