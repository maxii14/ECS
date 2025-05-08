#ifndef POOP_COLLECTOR_SYSTEM
#define POOP_COLLECTOR_SYSTEM

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

class PoopCollectorSystem final : public ISystem {
public:
    ComponentStorage<TransformComponent>& _transformComponents;
    Filter _transformFilter;

// public:
    PoopCollectorSystem(World &world)
    : ISystem(world),
    _transformComponents(world.GetStorage<TransformComponent>()),
    _transformFilter(FilterBuilder(world).With<TransformComponent>().Build()) {
        std::cout << "PoopCollectorSystem\n";
    }

    void OnInit() override { }

    void NotifyKeyboardEvent(sf::Keyboard::Key buttonCode) override { }

    void OnUpdate(sf::RenderWindow& window) override {
        for (const auto ent : _transformFilter) {
            auto& transform = _transformComponents.Get(ent);

            if (transform.position.x > 2000 || transform.position.y > 1500 || transform.position.x < -500 || transform.position.y < -500) {
            // if (transform.position.x > 2000 || transform.position.y > 1200 || transform.position.x < 300 || transform.position.y < 200) {
                if (world.IsEntityAlive(ent)) std::cout << "Entity dead " << ent << std::endl;
                world.RemoveEntity(ent);

            }
        }
    }
};

#endif //POOP_COLLECTOR_SYSTEM