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
#include "../components/TriangleShapeComponent.h"
#include "../IInitializer.hpp"
#include "../Filter.hpp"
#include "../FilterBuilder.hpp"
    

class ShootingSystem final : public ISystem {
public:
    ComponentStorage<TransformComponent>& _transformComponents;
    Filter _transforming;

// public:
    ShootingSystem(World &world)
    : ISystem(world),
    _transformComponents(world.GetStorage<TransformComponent>()),
    _transforming(FilterBuilder(world).With<TransformComponent>().Build()) {
        std::cout << "ShootingSystem";
    }

    void OnInit() override { }

    void OnUpdate(sf::RenderWindow& window) override {
        for (const auto ent : _transforming) {
            auto& transform = _transformComponents.Get(ent);
            if (transform.canManuallyRotate)
            {
                while (const std::optional event = world.window.pollEvent())
                {
                    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                    {
                        std::wcout << L"Key pressed with code = " << sf::Keyboard::getDescription(keyPressed->scancode).toWideString() << "\n";
                        std::cout << "SHOOOOT\n";

                        if (keyPressed->code == sf::Keyboard::Key::Space)
                        {
                            auto& rectangleStorage = world.GetStorage<RectangleShapeComponent>();
                            auto& transformsStorage = world.GetStorage<TransformComponent>();
                            auto& triangleStorage = world.GetStorage<TriangleShapeComponent>();

                            // Получаем трансформ ГЕИ
                            int playerId = triangleStorage.Entities()[0];
                            auto& playerTransform = _transformComponents.Get(playerId);
                            auto& playerTriangle = triangleStorage.Get(playerId);
                            
                            // Создаём пулю
                            int bullet = world.CreateEntity();
                            // получаем вершину игрока, задаём позицию и скорость
                            sf::Transform transform = playerTriangle._triangle.getTransform();
                            sf::Vector2f playerGunPos = transform.transformPoint(playerTriangle._triangle.getPoint(0));
                            float bulletSpeedX = (playerGunPos.x - playerTransform.position.x) / 10.0f;
                            float bulletSpeedY = (playerGunPos.y - playerTransform.position.y) / 10.0f;

                            transformsStorage.Add(bullet, TransformComponent(playerGunPos, {bulletSpeedX, bulletSpeedY}, playerTriangle._triangle.getRotation(), false));
                            rectangleStorage.Add(bullet, RectangleShapeComponent(3.0f, 10.0f));
                        }
                    }
                }
            }
        }
    }
};

#endif //SHOOTING_SYSTEM_H