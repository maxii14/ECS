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
#include "../components/CollisionComponent.h"
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
        std::cout << "ShootingSystem\n";
    }

    void OnInit() override {}

    void NotifyKeyboardEvent(sf::Keyboard::Key buttonCode) override {
        _buttonCode = buttonCode;
    }

    void OnUpdate(sf::RenderWindow& window) override {
        auto& playerStorage = world.GetStorage<PlayerComponent>();
        auto& bulletStorage = world.GetStorage<BulletComponent>();

        // Получаем трансформ ГЕИ
        int playerId = playerStorage.Entities()[0];
        if (!world.IsEntityAlive(playerId)) return;
        auto& playerTransform = _transformComponents.Get(playerId);


        for (const auto ent : _transforming) {
            auto& transform = _transformComponents.Get(ent);
            if (_buttonCode == sf::Keyboard::Key::Space)
            {
                _buttonCode = sf::Keyboard::Key::Unknown;

                // Создаём пулю
                int bullet = world.CreateEntity(bulletStorage);

                const auto& createdBullets = bulletStorage.Entities();
                if (std::find(createdBullets.begin(), createdBullets.end(), bullet) != createdBullets.end()) {
                    RespawnBullet(bullet);
                }
                else {
                    SpawnBullet(bullet);
                }
            }
        }
    }

    void SpawnBullet(int bullet) {

        auto& rectangleStorage = world.GetStorage<RectangleShapeComponent>();
        auto& transformStorage = world.GetStorage<TransformComponent>();
        auto& playerStorage = world.GetStorage<PlayerComponent>();
        auto& bulletStorage = world.GetStorage<BulletComponent>();
        auto& boxColliderStorage = world.GetStorage<BoxColliderComponent>();
        auto& collisionStorage = world.GetStorage<CollisionComponent>();
        int playerId = playerStorage.Entities()[0];
        auto& playerTransform = _transformComponents.Get(playerId);
        auto& circleStorage = world.GetStorage<CircleShapeComponent>();
        auto& playerCircle = circleStorage.Get(playerId);

        // получаем вершину игрока, задаём позицию и скорость
        sf::Transform transform = playerCircle._polygon.getTransform();
        sf::Vector2f playerGunPos = transform.transformPoint(playerCircle._polygon.getPoint(0));
        float bulletSpeedX = (playerGunPos.x - playerTransform.position.x) / 2.0f;
        float bulletSpeedY = (playerGunPos.y - playerTransform.position.y) / 2.0f;
        // std::cout << bulletSpeedX << ", " << bulletSpeedY << std::endl;
        transformStorage.Add(bullet, TransformComponent(
            playerGunPos,
            {bulletSpeedX, bulletSpeedY},
            playerCircle._polygon.getRotation(),
            false
        ));
        float bullet_xSize = 1.5f;
        float bullet_ySize = 20.0f;
        rectangleStorage.Add(bullet, RectangleShapeComponent(bullet_xSize, bullet_ySize));
        bulletStorage.Add(bullet, BulletComponent());
        boxColliderStorage.Add(bullet, BoxColliderComponent(bullet_xSize, bullet_ySize, playerGunPos + sf::Vector2f{bullet_xSize / 2.0f, bullet_ySize / 2.0f}));
        collisionStorage.Add(bullet, CollisionComponent());
    }

    void RespawnBullet(int bullet) {
        auto& playerStorage = world.GetStorage<PlayerComponent>();
        int playerId = playerStorage.Entities()[0];
        auto& playerTransform = _transformComponents.Get(playerId);

        auto& circleStorage = world.GetStorage<CircleShapeComponent>();
        auto& boxColliderStorage = world.GetStorage<BoxColliderComponent>();
        auto& boxCollider = boxColliderStorage.Get(bullet);
        auto& playerCircle = circleStorage.Get(playerId);
        auto& bulletTransformComponent = _transformComponents.Get(bullet);

        sf::Transform transform = playerCircle._polygon.getTransform();
        sf::Vector2f playerGunPos = transform.transformPoint(playerCircle._polygon.getPoint(0));

        float bulletSpeedX = (playerGunPos.x - playerTransform.position.x) / 2.0f;
        float bulletSpeedY = (playerGunPos.y - playerTransform.position.y) / 2.0f;

        bulletTransformComponent.position = playerGunPos;
        bulletTransformComponent.speed = {bulletSpeedX, bulletSpeedY};

        bulletTransformComponent.rotationSpeed = playerCircle._polygon.getRotation();
        boxCollider._refPoint = playerGunPos;

    }
};

#endif //SHOOTING_SYSTEM_H