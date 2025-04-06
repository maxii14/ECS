#ifndef INIT_SYSTEM_H
#define INIT_SYSTEM_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "../ConfigReader.h"
#include "../components/Sprite.h"

class InitSystem {
    ConfigReader& _configReader;
    std::shared_ptr<Sprite> _sprite;

public:
    InitSystem() = default;
    InitSystem(ConfigReader configReader);
};

#endif //INIT_SYSTEM_H