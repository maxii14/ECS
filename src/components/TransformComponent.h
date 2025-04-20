#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

struct TransformComponent {
    sf::Vector2f position;
    //sf::Vector2f scale;
    sf::Vector2f speed;

    TransformComponent(sf::Vector2f pos, sf::Vector2f sp): position(pos), speed(sp)
    {
       
    }
    TransformComponent()
    {
        
    }
};

#endif //TRANSFORM_COMPONENT_H