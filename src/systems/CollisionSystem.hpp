#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "../ComponentStorage.hpp"
#include "../components/Position.h"
#include "../components/BoxColliderComponent.h"
#include "../components/CircleColliderComponent.h"
#include "../IInitializer.hpp"
#include "../Filter.hpp"
#include "../FilterBuilder.hpp"

class CollisionSystem final : public ISystem {
public:
    ComponentStorage<BoxColliderComponent>& _boxComponents;
    ComponentStorage<CircleColliderComponent>& _circleComponents;
    Filter _meteors;
    Filter _playerAndBullets;

// public:
    CollisionSystem(World &world)
    : ISystem(world),
    _boxComponents(world.GetStorage<BoxColliderComponent>()),
    _circleComponents(world.GetStorage<CircleColliderComponent>()),
    _meteors(FilterBuilder(world).With<CircleColliderComponent>().Build()),
    _playerAndBullets(FilterBuilder(world).With<BoxColliderComponent>().Build()) {
        std::cout << "CollisionSystem";
    }

    void OnInit() override { }

    void NotifyKeyboardEvent(sf::Keyboard::Key buttonCode) override { }

    void OnUpdate(sf::RenderWindow& window) override {
        for (const auto pObject : _playerAndBullets) {
            for (const auto nObject : _meteors) {
                auto& circleCollider = _circleComponents.Get(nObject);
                auto& boxCollider = _boxComponents.Get(pObject);
                // circleCollider._refPoint
            }
        }
    }
};

#endif //COLLISION_SYSTEM_H