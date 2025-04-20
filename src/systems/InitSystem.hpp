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
#include "../components/TransformComponent.h"
#include "../IInitializer.hpp"
#include "../components/RectangleShapeComponent.h"
#include "../components/TriangleShapeComponent.h"

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
        const int player1 = world.CreateEntity();
        auto& positionsStorage = world.GetStorage<Position>();

        auto& transformsStorage = world.GetStorage<TransformComponent>();
        auto& rectangleStorage = world.GetStorage<RectangleShapeComponent>();
        auto& triangleStorage = world.GetStorage<TriangleShapeComponent>();
        
        transformsStorage.Add(player, TransformComponent({0.0f, 0.0f}, {5.0f, 5.0f}));
        rectangleStorage.Add(player, RectangleShapeComponent(100.0f, 100.0f));
        transformsStorage.Add(player1, TransformComponent({0.0f, 0.0f}, {10.0f, 10.0f}));
        triangleStorage.Add(player1, TriangleShapeComponent(200.0f, 3));
    }
};

#endif //INIT_SYSTEM_H