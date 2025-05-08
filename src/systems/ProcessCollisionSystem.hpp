#ifndef PROCESS_COLLISION_SYSTEM_H
#define PROCESS_COLLISION_SYSTEM_H

#include <memory>
#include <vector>
#include <string>
#include <iostream>

#include "../Filter.hpp"
#include "../IInitializer.hpp"
#include "../FilterBuilder.hpp"
#include "../ComponentStorage.hpp"

#include "../components/CollisionComponent.h"


class ProcessCollisionSystem final : public ISystem {
public:
    ComponentStorage<CollisionComponent>& _collisionComponents;

    Filter _collisioningFilter;

    ProcessCollisionSystem(World &world)
    : ISystem(world),
    _collisionComponents(world.GetStorage<CollisionComponent>()),
    _collisioningFilter(FilterBuilder(world).With<CollisionComponent>().Build()) {
        std::cout << "ProcessCollisionSystem\n";
    }

    void OnInit() override { }

    void NotifyKeyboardEvent(sf::Keyboard::Key buttonCode) override { }

    void OnUpdate(sf::RenderWindow& window) override {
        for (const auto ent : _collisioningFilter) {
            auto& collision = _collisionComponents.Get(ent);
            for (auto entId : collision.collisionWithComponents) {
                world.RemoveEntity(entId);
            }
            collision.collisionWithComponents.clear();
        }
    }
};

#endif //PROCESS_COLLISION_SYSTEM_H