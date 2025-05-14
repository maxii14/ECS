#ifndef RESPAWN_SYSTEM_H
#define RESPAWN_SYSTEM_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "../ComponentStorage.hpp"
#include "../IInitializer.hpp"
#include "../Filter.hpp"
#include "../FilterBuilder.hpp"
#include "../components/PlayerComponent.h"

class RespawnSystem final : public ISystem {
public:
    ComponentStorage<PlayerComponent>& _playerComponents;
    ComponentStorage<TransformComponent>& _transformComponents;
    Filter _playerFilter, _transformFilter;
    sf::Keyboard::Key _buttonCode = sf::Keyboard::Key::Unknown;

    RespawnSystem(World &world)
    : ISystem(world),
    _playerComponents(world.GetStorage<PlayerComponent>()),
    _transformComponents(world.GetStorage<TransformComponent>()),
    _playerFilter(FilterBuilder(world).With<PlayerComponent>().Build()),
    _transformFilter(FilterBuilder(world).With<TransformComponent>().Build()) {
        std::cout << "PotrachenoSystem\n";
    }

    void OnInit() override { }

    void NotifyKeyboardEvent(sf::Keyboard::Key buttonCode) override {
        _buttonCode = buttonCode;
    }

    void OnUpdate(sf::RenderWindow& window, std::shared_ptr<Text> text) override {
        for (const auto ent : _playerFilter) {
            auto& player = _playerComponents.Get(ent);

            // ГЕИ мёртва и нажат пробел => возрождаем
            if (!world.IsEntityAlive(ent)) {
                if (_buttonCode == sf::Keyboard::Key::Enter) {
                    auto& playerStorage = world.GetStorage<PlayerComponent>();
                    int player = world.CreateEntity(playerStorage);

                    text->SetPosition({30.f, 30.f});
                }
            }
        }
        _buttonCode = sf::Keyboard::Key::Unknown;
    }
};

#endif //RESPAWN_SYSTEM_H