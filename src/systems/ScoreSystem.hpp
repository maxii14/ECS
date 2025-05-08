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
    ComponentStorage<CollisionComponent>& _collisionComponents;
    Filter _bullet;

    ScoreSystem(World &world)
    : ISystem(world),
    _collisionComponents(world.GetStorage<CollisionComponent>()),
    _bullet(FilterBuilder(world).With<CollisionComponent>().With<BulletComponent>().Build()){
        std::cout << "ScoreSystem\n";
    }

    void OnInit() override { }

    void NotifyKeyboardEvent(sf::Keyboard::Key buttonCode) override { }

    void OnUpdate(sf::RenderWindow& window, std::shared_ptr<Text> text) override {
        int score = text->GetScore();
        for (int bulletId : _bullet) {
            auto& collision = _collisionComponents.Get(bulletId);
            auto& collisionList = collision.collisionWithComponents;
            score += collisionList.size()*100;
        }
        text->SetText("Score: " + std::to_string(score));
    }
};

#endif //SCORE_SYSTEM_H