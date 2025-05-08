#ifndef ROTATION_SYSTEM_H
#define ROTATION_SYSTEM_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "../ComponentStorage.hpp"
#include "../components/Position.h"
#include "../components/PlayerComponent.h"
#include "../components/TransformComponent.h"
#include "../IInitializer.hpp"
#include "../Filter.hpp"
#include "../FilterBuilder.hpp"

class RotationSystem final : public ISystem {
public:
    ComponentStorage<TransformComponent>& _transformComponents;
    Filter _playerFilter;
    sf::Keyboard::Key _buttonCode = sf::Keyboard::Key::Unknown;

// public:
    RotationSystem(World &world)
    : ISystem(world),
    _transformComponents(world.GetStorage<TransformComponent>()),
    _playerFilter(
        FilterBuilder(world)\
            .With<TransformComponent>()\
            .With<PlayerComponent>()\
            .Build()\
    ) {
        std::cout << "RotationSystem\n";
    }

    void OnInit() override { }

    void NotifyKeyboardEvent(sf::Keyboard::Key buttonCode) override {
        _buttonCode = buttonCode;
    }

    void OnUpdate(sf::RenderWindow& window, std::shared_ptr<Text> text) override {
        for (const auto ent : _playerFilter) {
            auto& transform = _transformComponents.Get(ent);
            transform.rotationSpeed = sf::degrees(0);

            if (_buttonCode == sf::Keyboard::Key::Left)
            {
                transform.rotationSpeed = sf::degrees(-7);
            }
            if (_buttonCode == sf::Keyboard::Key::Right)
            {
                transform.rotationSpeed = sf::degrees(7);
            }
        }
        _buttonCode = sf::Keyboard::Key::Unknown;
    }
};

#endif //ROTATION_SYSTEM_H