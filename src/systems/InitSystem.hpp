#ifndef INIT_SYSTEM_H
#define INIT_SYSTEM_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "../ConfigReader.h"
#include "../components/Sprite.h"
#include "../components/Position.h"
#include "../components/TransformComponent.h"
#include "../IInitializer.hpp"
#include "../components/RectangleShapeComponent.h"
#include "../components/CircleShapeComponent.h"
#include "../components/PlayerComponent.h"
#include "../components/MeteorComponent.h"
#include "../components/BoxColliderComponent.h"
#include "../components/CircleColliderComponent.h"


class InitSystem final : public IInitializer {
public:
    InitSystem(World &world) : IInitializer(world) { }
    void OnInit() override {
        // Инициализируем сторэджи
        auto& positionsStorage = world.GetStorage<Position>();
        auto& transformsStorage = world.GetStorage<TransformComponent>();
        auto& polygonStorage = world.GetStorage<CircleShapeComponent>();
        auto& playerStorage = world.GetStorage<PlayerComponent>();
        auto& meteorStorage = world.GetStorage<MeteorComponent>();
        auto& circleColliderStorage = world.GetStorage<CircleColliderComponent>();
        auto& boxColliderStorage = world.GetStorage<BoxColliderComponent>();

        // Инициализиуем Главную Единицу-Игрок (ГЕИ)
        const int player = world.CreateEntity();
        float playerPosX = 640.0f, playerPosY = 360.0f, playerRadius = 50.0f;
        transformsStorage.Add(player, TransformComponent({playerPosX, playerPosY}, {0.0f, 0.0f}, sf::degrees(0), true));
        float playerColor[3] = {1.0f, 1.0f, 1.0f};
        polygonStorage.Add(player, CircleShapeComponent(playerRadius, 3, playerColor));
        playerStorage.Add(player, PlayerComponent());
        boxColliderStorage.Add(player, BoxColliderComponent(playerRadius*2.0f, playerRadius*2.0f, {playerPosX - playerRadius, playerPosY - playerRadius}));

        // Инициализируем метеориты
        for (int i = 0; i < 40; i++) {
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
            float speedX = (playerPosX - posX) / 1600.0f * (2 + rand() % 5);
            float speedY = (playerPosY - posY) / 1600.0f * (2 + rand() % 7);
            float rotationSpeed = rand() % 6;
            transformsStorage.Add(meteor, TransformComponent({posX, posY}, {speedX, speedY}, sf::degrees(rotationSpeed), false));
            circleColliderStorage.Add(meteor, CircleColliderComponent(size_rand, {posX, posY}));
        }

        // transformsStorage.Add(player, TransformComponent({0.0f, 0.0f}, {1.0f, 1.0f}, sf::degrees(0), false));
        // rectangleStorage.Add(player, RectangleShapeComponent(100.0f, 100.0f));
    }
};

#endif //INIT_SYSTEM_H