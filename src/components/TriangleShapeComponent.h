#ifndef TRIANGLE_SHAPE_COMPONENT_H
#define TRIANGLE_SHAPE_COMPONENT_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>


struct TriangleShapeComponent
{
    float _radius;
    int _angles;
    float _color[3] = { 1.0f, 1.0f, 1.0f };
    sf::CircleShape _triangle;

    TriangleShapeComponent(float radius, float angles): _radius(radius), _angles(angles)
    {
        _triangle = sf::CircleShape(radius, angles);
        _triangle.setFillColor(sf::Color(
            _color[0]*255,
            _color[1]*255,
            _color[2]*255
        ));
        _triangle.setOrigin({radius, radius});
    }
    TriangleShapeComponent(): _radius(100.0f), _angles(3)
    {
        _triangle = sf::CircleShape(_radius, _angles);
        _triangle.setFillColor(sf::Color(
            _color[0]*255,
            _color[1]*255,
            _color[2]*255
        ));
    }
};

#endif //TRIANGLE_SHAPE_COMPONENT_H