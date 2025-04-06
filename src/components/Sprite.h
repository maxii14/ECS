#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

struct Sprite {
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif //SPRITE_H