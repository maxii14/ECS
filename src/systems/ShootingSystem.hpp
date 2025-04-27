#ifndef SHOOTING_SYSTEM_H
#define SHOOTING_SYSTEM_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "../ComponentStorage.hpp"
#include "../components/Position.h"
#include "../components/TransformComponent.h"
#include "../components/RectangleShapeComponent.h"
#include "../components/CircleShapeComponent.h"
#include "../components/PlayerComponent.h"
#include "../components/BulletComponent.h"
#include "../components/BoxColliderComponent.h"
#include "../IInitializer.hpp"
#include "../Filter.hpp"
#include "../FilterBuilder.hpp"


class ShootingSystem final : public ISystem {
public:
    ComponentStorage<TransformComponent>& _transformComponents;
    Filter _transforming;
    sf::Keyboard::Key _buttonCode = sf::Keyboard::Key::Unknown;

// public:
    ShootingSystem(World &world)
    : ISystem(world),
    _transformComponents(world.GetStorage<TransformComponent>()),
    _transforming(FilterBuilder(world).With<TransformComponent>().With<PlayerComponent>().Build()) {
        std::cout << "ShootingSystem";
    }

    void OnInit() override { }

    void NotifyKeyboardEvent(sf::Keyboard::Key buttonCode) override {
        _buttonCode = buttonCode;
    }

    void OnUpdate(sf::RenderWindow& window) override {
        for (const auto ent : _transforming) {
            auto& transform = _transformComponents.Get(ent);
            if (_buttonCode == sf::Keyboard::Key::Space)
            {
                _buttonCode = sf::Keyboard::Key::Unknown;

                auto& rectangleStorage = world.GetStorage<RectangleShapeComponent>();
                auto& transformStorage = world.GetStorage<TransformComponent>();
                auto& playerStorage = world.GetStorage<PlayerComponent>();
                auto& circleStorage = world.GetStorage<CircleShapeComponent>();
                auto& bulletStorage = world.GetStorage<BulletComponent>();
                auto& boxColliderStorage = world.GetStorage<BoxColliderComponent>();

                // Получаем трансформ ГЕИ
                int playerId = playerStorage.Entities()[0];
                auto& playerTransform = _transformComponents.Get(playerId);
                auto& playerCircle = circleStorage.Get(playerId);

                // Создаём пулю
                int bullet = world.CreateEntity();
                // получаем вершину игрока, задаём позицию и скорость
                sf::Transform transform = playerCircle._polygon.getTransform();
                sf::Vector2f playerGunPos = transform.transformPoint(playerCircle._polygon.getPoint(0));
                float bulletSpeedX = (playerGunPos.x - playerTransform.position.x) / 2.0f;
                float bulletSpeedY = (playerGunPos.y - playerTransform.position.y) / 2.0f;

                transformStorage.Add(bullet, TransformComponent(
                    playerGunPos,
                    {bulletSpeedX, bulletSpeedY},
                    playerCircle._polygon.getRotation(),
                    false
                ));
                float bullet_xSize = 2.0f;
                float bullet_ySize = 15.0f;
                rectangleStorage.Add(bullet, RectangleShapeComponent(bullet_xSize, bullet_ySize));
                bulletStorage.Add(bullet, BulletComponent());
                boxColliderStorage.Add(bullet, BoxColliderComponent(bullet_xSize, bullet_ySize, playerGunPos));
            }
        }
    }
};

#endif //SHOOTING_SYSTEM_H