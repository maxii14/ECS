#ifndef METEOR_SPAWN_SYSTEM_H
#define METEOR_SPAWN_SYSTEM_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "../ConfigReader.h"
#include "../components/TransformComponent.h"
#include "../IInitializer.hpp"
#include "../components/RectangleShapeComponent.h"
#include "../components/CircleShapeComponent.h"
#include "../components/PlayerComponent.h"
#include "../components/MeteorComponent.h"
#include "../components/BoxColliderComponent.h"
#include "../components/CircleColliderComponent.h"
#include "../components/CollisionComponent.h"
#include "../ComponentStorage.hpp"
#include "../Filter.hpp"
#include "../FilterBuilder.hpp"


class MeteorSpawnSystem final : public ISystem {
public:
    int meteorsTotalCount;
    ComponentStorage<TransformComponent>& _transformComponents;
    Filter _meteorFilter;

    MeteorSpawnSystem(World &world)
    : ISystem(world),
    _transformComponents(world.GetStorage<TransformComponent>()),
    _meteorFilter(FilterBuilder(world).With<TransformComponent>().With<MeteorComponent>().Build()) {
        std::cout << "MeteorSpawnSystem\n";
        meteorsTotalCount = 10;
    }

    void OnInit() override {
        SpawnMeteors();
    }

    void NotifyKeyboardEvent(sf::Keyboard::Key buttonCode) override { }

    void OnUpdate(sf::RenderWindow& window) override {
        int mCount = 0;
        for (const auto ent : _meteorFilter) {
            if (world.IsEntityAlive(ent)) mCount++;
        }

        if (mCount == meteorsTotalCount) return;
        int missingMeteorsCount = meteorsTotalCount - mCount;

        RespawnMeteors(missingMeteorsCount);
    }

    void SpawnMeteors() {
        // Инициализируем сторэджи
        auto& positionsStorage = world.GetStorage<Position>();
        auto& transformsStorage = world.GetStorage<TransformComponent>();
        auto& playerStorage = world.GetStorage<PlayerComponent>();
        auto& polygonStorage = world.GetStorage<CircleShapeComponent>();
        auto& meteorStorage = world.GetStorage<MeteorComponent>();
        auto& circleColliderStorage = world.GetStorage<CircleColliderComponent>();
        auto& collisionStorage = world.GetStorage<CollisionComponent>();

        int playerId = playerStorage.Entities()[0];
        auto& playerTransform = _transformComponents.Get(playerId);

        // Спавним метеориты первый раз
        for (int i = 0; i < meteorsTotalCount; i++) {
            int meteor = world.CreateEntity();
            // Размеры и форма
            float size_rand = 10 + rand() % 51;
            int angles_number_rand = 4 + rand() % 5;
            float grayScaleColor = (30 + rand() % 150) / 255.0f;
            float meteorColor[3] = {grayScaleColor, grayScaleColor, grayScaleColor};
            polygonStorage.Add(meteor, CircleShapeComponent(size_rand, angles_number_rand, meteorColor));
            meteorStorage.Add(meteor, MeteorComponent());

            // Позиция
            int sideX = rand() % 2, sideY = rand() % 2, side = rand() % 3;
            float posX, posY;
            switch (side)
            {
            case 0: // слева-справа, sideY ne ebet
                if (sideX == 0) posX = -200.0f; // метеорит спавнится слева
                else posX = 1280.0f + 200.0f; // метеорит спавнится cправа
                posY = rand() % 721;
                break;
            case 1: // снизу-сверху, sideX ne ebet
                if (sideY == 0) posY = -200.0f; // метеорит спавнится сверху
                else posY = 720.0f + 200.0f; // метеорит спавнится cнизу
                posX = rand() % 1281;
                break;
            default: // по диагонали
                if (sideX == 0) posX = -200.0f - rand() % 201;
                else posX = 1280.0f + 200.0f + rand() % 201;
                if (sideY == 0) posY = -200.0f - rand() % 201;
                else posY = 720.0f + 200.0f + rand() % 201;
                break;
            }

            // Скорость
            float speedX = (playerTransform.position.x - posX) / 1600.0f * (2 + rand() % 5);
            float speedY = (playerTransform.position.y - posY) / 1600.0f * (2 + rand() % 7);
            float rotationSpeed = rand() % 6;
            transformsStorage.Add(meteor, TransformComponent({posX, posY}, {speedX, speedY}, sf::degrees(rotationSpeed), false));
            circleColliderStorage.Add(meteor, CircleColliderComponent(size_rand, {posX, posY}));
            collisionStorage.Add(meteor, CollisionComponent());
        }
    }

    void RespawnMeteors(int count) {
        auto& playerStorage = world.GetStorage<PlayerComponent>();
        int playerId = playerStorage.Entities()[0];
        auto& playerTransform = _transformComponents.Get(playerId);
        auto& meteorStorage = world.GetStorage<MeteorComponent>();
        auto& circleColliderStorage = world.GetStorage<CircleColliderComponent>();

        // Переспавниваем недостающие метеориты
        for (int i = 0; i < count; i++) {

            int meteor = world.CreateEntity(meteorStorage);
            auto& meteorTransform = _transformComponents.Get(meteor);
            auto& circleCollider = circleColliderStorage.Get(meteor);

            // Позиция
            int sideX = rand() % 2, sideY = rand() % 2, side = rand() % 3;
            float posX, posY;
            switch (side)
            {
            case 0: // слева-справа, sideY ne ebet
                if (sideX == 0) posX = -200.0f; // метеорит спавнится слева
                else posX = 1280.0f + 200.0f; // метеорит спавнится cправа
                posY = rand() % 721;
                break;
            case 1: // снизу-сверху, sideX ne ebet
                if (sideY == 0) posY = -200.0f; // метеорит спавнится сверху
                else posY = 720.0f + 200.0f; // метеорит спавнится cнизу
                posX = rand() % 1281;
                break;
            default: // по диагонали
                if (sideX == 0) posX = -200.0f - rand() % 201;
                else posX = 1280.0f + 200.0f + rand() % 201;
                if (sideY == 0) posY = -200.0f - rand() % 201;
                else posY = 720.0f + 200.0f + rand() % 201;
                break;
            }

            meteorTransform.position.x = posX;
            meteorTransform.position.y = posY;

            // Скорость
            float speedX = (playerTransform.position.x - posX) / 1600.0f * (2 + rand() % 5);
            float speedY = (playerTransform.position.y - posY) / 1600.0f * (2 + rand() % 7);

            meteorTransform.speed.x = speedX;
            meteorTransform.speed.y = speedY;
            circleCollider._refPoint = {posX, posY};
        }
    }
};

#endif //METEOR_SPAWN_SYSTEM_H