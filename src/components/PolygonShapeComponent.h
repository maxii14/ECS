#ifndef POLYGON_SHAPE_COMPONENT_H
#define POLYGON_SHAPE_COMPONENT_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>


struct PolygonShapeComponent
{
    float _radius;
    int _angles;
    float _color[3] = { 1.0f, 1.0f, 1.0f };
    sf::CircleShape _polygon;

    PolygonShapeComponent(float radius, size_t angles, float* color): _radius(radius), _angles(angles)
    {
        _polygon = sf::CircleShape(radius, angles);
        _color[0] = color[0];
        _color[1] = color[1];
        _color[2] = color[2];
        _polygon.setFillColor(sf::Color(
            _color[0]*255,
            _color[1]*255,
            _color[2]*255
        ));
        _polygon.setOrigin({radius, radius});
    }
    PolygonShapeComponent(): _radius(100.0f), _angles(4)
    {
        _polygon = sf::CircleShape(_radius, _angles);
        _polygon.setFillColor(sf::Color(
            _color[0]*255,
            _color[1]*255,
            _color[2]*255
        ));
    }
};

#endif //POLYGON_SHAPE_COMPONENT_H