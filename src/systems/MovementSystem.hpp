#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "../ComponentStorage.hpp"
#include "../components/Position.h"
#include "../components/TransformComponent.h"
#include "../IInitializer.hpp"
#include "../Filter.hpp"
#include "../FilterBuilder.hpp"

class MovementSystem final : public ISystem {
public:
    ComponentStorage<Position>& _positionComponents;
    ComponentStorage<TransformComponent>& _transformComponents;
    Filter _positioning, _transforming;

// public:
    MovementSystem(World &world)
    : ISystem(world),
    _positionComponents(world.GetStorage<Position>()),
    _positioning(FilterBuilder(world).With<Position>().Build()),
    _transformComponents(world.GetStorage<TransformComponent>()),
    _transforming(FilterBuilder(world).With<TransformComponent>().Build()) {
        std::cout << "MovementSystem";
    }

    void OnInit() override { }

    void OnUpdate(sf::RenderWindow& window) override {
        for (const auto ent : _positioning) {
            // float x = static_cast <float> (rand() % 5);
            // float y = static_cast <float> (rand() % 5);

            // auto& position = _positionComponents.Get(ent);
            // position.X += x;
            // position.Y += y;
            auto& transform = _transformComponents.Get(ent);
            transform.position += transform.speed;
            //std::cout << ent << " Pos: " << position.X << std::endl;
        }
    }
};

#endif //MOVEMENT_SYSTEM_H