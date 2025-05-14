#ifndef SHOOTING_DELAY_SYSTEM_H
#define SHOOTING_DELAY_SYSTEM_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "../ComponentStorage.hpp"
#include "../IInitializer.hpp"
#include "../Filter.hpp"
#include "../FilterBuilder.hpp"
#include "../components/PlayerComponent.h"

class ShootingDelaySystem final : public ISystem {
public:
    ComponentStorage<PlayerComponent>& _playerComponents;
    Filter _playerFilter;

    ShootingDelaySystem(World &world)
    : ISystem(world),
    _playerComponents(world.GetStorage<PlayerComponent>()),
    _playerFilter(FilterBuilder(world).With<PlayerComponent>().Build()) {
        std::cout << "ShootingDelaySystem\n";
    }

    void OnInit() override { }

    void NotifyKeyboardEvent(sf::Keyboard::Key buttonCode) override { }

    void OnUpdate(sf::RenderWindow& window, std::shared_ptr<Text> text) override {
        for (const auto ent : _playerFilter) {
            auto& player = _playerComponents.Get(ent);
            if (player.delay < 30) player.delay++;
        }
    }
};

#endif //SHOOTING_DELAY_SYSTEM_H