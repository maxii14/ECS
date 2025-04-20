#ifndef RECTANGLE_SHAPE_COMPONENT_H
#define RECTANGLE_SHAPE_COMPONENT_H

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>


struct RectangleShapeComponent
{
    float _xSize;
    float _ySize;
    float _color[3] = { 1.0f, 1.0f, 1.0f };
    sf::RectangleShape _rectangle;

    RectangleShapeComponent(float xSize, float ySize): _xSize(xSize), _ySize(ySize)
    {
        _rectangle = sf::RectangleShape({_xSize, _ySize});
        _rectangle.setFillColor(sf::Color(
            _color[0]*255,
            _color[1]*255,
            _color[2]*255
        ));
    }
    RectangleShapeComponent(): _xSize(100.0f), _ySize(100.0f)
    {
        _rectangle = sf::RectangleShape({0, 0});
        _rectangle.setFillColor(sf::Color(
            _color[0]*255,
            _color[1]*255,
            _color[2]*255
        ));
    }
};

#endif //RECTANGLE_SHAPE_COMPONENT_H