#ifndef POTRACHENO_SYSTEM_H
#define POTRACHENO_SYSTEM_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "../ComponentStorage.hpp"
#include "../IInitializer.hpp"
#include "../Filter.hpp"
#include "../FilterBuilder.hpp"
#include "../components/PlayerComponent.h"

class PotrachenoSystem final : public ISystem {
public:
    ComponentStorage<PlayerComponent>& _playerComponents;
    ComponentStorage<TransformComponent>& _transformComponents;
    Filter _playerFilter, _transformFilter;

    PotrachenoSystem(World &world)
    : ISystem(world),
    _playerComponents(world.GetStorage<PlayerComponent>()),
    _transformComponents(world.GetStorage<TransformComponent>()),
    _playerFilter(FilterBuilder(world).With<PlayerComponent>().Build()),
    _transformFilter(FilterBuilder(world).With<TransformComponent>().Build()) {
        std::cout << "PotrachenoSystem\n";
    }

    void OnInit() override { }

    void NotifyKeyboardEvent(sf::Keyboard::Key buttonCode) override { }

    void OnUpdate(sf::RenderWindow& window, std::shared_ptr<Text> text) override {
        for (const auto ent : _playerFilter) {
            if (!world.IsEntityAlive(ent)) {
                auto& player = _playerComponents.Get(ent);
                player.score = 0;

                for (const auto ent1 : _transformFilter) {
                    world.RemoveEntity(ent1);
                }
                text->SetPosition({640.0f - text->GetCharacterSize() * 13 / 3.800555353500040091008880000001f, 360.0f - text->GetCharacterSize()});
                text->SetText("POTRACHENO(((\n\tPRESS ENTER");
            }
        }
    }
};

#endif //POTRACHENO_SYSTEM_H