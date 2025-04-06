#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

struct Transform {
    sf::Vector2f position = {0.0f, 0.0f};
    sf::Vector2f scale = {1.0f, 1.0f};
    sf::Vector2f speed = {1.0f, 1.0f};
};

#endif //TRANSFORM_H