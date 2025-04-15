#ifndef INIT_SYSTEM_H
#define INIT_SYSTEM_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "../ConfigReader.h"
#include "../components/Sprite.h"
#include "../components/Position.h"
#include "../IInitializer.hpp"

// class InitSystem {
//     ConfigReader& _configReader;
//     std::shared_ptr<Sprite> _sprite;

// public:
//     InitSystem() = default;
//     InitSystem(ConfigReader configReader);
// };

class InitSystem final : public IInitializer {
public:
    InitSystem(World &world) : IInitializer(world) { }
    void OnInit() override {
        const int player = world.CreateEntity();
        auto& positionsStorage = world.GetStorage<Position>();
        // сюда нам надо
        positionsStorage.Add(player, Position(0, 0));
    }
};

#endif //INIT_SYSTEM_H