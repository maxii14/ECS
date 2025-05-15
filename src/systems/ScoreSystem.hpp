#ifndef SCORE_SYSTEM_H
#define SCORE_SYSTEM_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "../ComponentStorage.hpp"
#include "../components/CollisionComponent.h"
#include "../IInitializer.hpp"
#include "../Filter.hpp"
#include "../FilterBuilder.hpp"
#include "../components/BulletComponent.h"
#include "../Text.h"

class ScoreSystem final : public ISystem {
public:
    ComponentStorage<PlayerComponent>& _playerComponents;
    Filter _playerFilter;
    ComponentStorage<CollisionComponent>& _collisionComponents;
    Filter _bullet;

    ScoreSystem(World &world)
    : ISystem(world),
    _collisionComponents(world.GetStorage<CollisionComponent>()),
    _playerComponents(world.GetStorage<PlayerComponent>()),
    _playerFilter(FilterBuilder(world).With<PlayerComponent>().Build()),
    _bullet(FilterBuilder(world).With<CollisionComponent>().With<BulletComponent>().Build()){
        std::cout << "ScoreSystem\n";
    }

    void OnInit() override { }

    void NotifyKeyboardEvent(sf::Keyboard::Key buttonCode) override { }

    void OnUpdate(sf::RenderWindow& window, std::shared_ptr<Text> text) override {
        auto& player = _playerComponents.Get(0);

        for (int bulletId : _bullet) {
            auto& collision = _collisionComponents.Get(bulletId);
            auto& collisionList = collision.collisionWithComponents;
            player.score += collisionList.size()*world.configReader.GetKillPoints();
        }
        text->SetText("Score: " + std::to_string((int)player.score));
    }
};

#endif //SCORE_SYSTEM_H