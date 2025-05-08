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
#include "../components/CollisionComponent.h"


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
        auto& collisionStorage = world.GetStorage<CollisionComponent>();

        // Инициализиуем Главную Единицу-Игрок (ГЕИ)
        const int player = world.CreateEntity();
        float playerPosX = 640.0f, playerPosY = 360.0f, playerRadius = 50.0f;
        transformsStorage.Add(player, TransformComponent({playerPosX, playerPosY}, {0.0f, 0.0f}, sf::degrees(0), true));
        float playerColor[3] = {1.0f, 1.0f, 1.0f};
        polygonStorage.Add(player, CircleShapeComponent(playerRadius, 3, playerColor));
        playerStorage.Add(player, PlayerComponent());
        boxColliderStorage.Add(player, BoxColliderComponent(playerRadius*2.0f, playerRadius*2.0f, {playerPosX, playerPosY}));
        collisionStorage.Add(player, CollisionComponent());

    }
};

#endif //INIT_SYSTEM_H