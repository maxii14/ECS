#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "../ComponentStorage.h"
#include "../components/Position.h"
#include "../IInitializer.hpp"
#include "../Filter.hpp"
#include "../FilterBuilder.hpp"

class MovementSystem final : public ISystem {
    ComponentStorage<Position>& _positionComponents;
    Filter _positioning;

public:
    MovementSystem(World &world)
    : ISystem(world),
    _positionComponents(world.GetStorage<Position>()),
    _positioning(FilterBuilder(world).With<Position>().Build()) { 

    }

    void OnInit() override { }

    void OnUpdate() override {
        for (const auto ent : _positioning) {
            auto& position = _positionComponents.Get(ent);
            position.X += 1.5;
            std::cout << ent << " Pos: " << position.X << std::endl;
        }
    }
};

#endif //MOVEMENT_SYSTEM_H