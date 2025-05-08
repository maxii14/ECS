#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "../ComponentStorage.hpp"
#include "../components/Position.h"
#include "../components/TransformComponent.h"
#include "../IInitializer.hpp"
#include "../Filter.hpp"
#include "../FilterBuilder.hpp"
#include "../components/RectangleShapeComponent.h"
#include "../components/CircleShapeComponent.h"
#include "../components/PlayerComponent.h"
#include "../components/MeteorComponent.h"
#include "../components/BulletComponent.h"
#include "../Text.h"

class RenderSystem final : public ISystem {
public:
    ComponentStorage<TransformComponent>& _transformComponents;
    ComponentStorage<CircleShapeComponent>& _circleShapeComponents;
    ComponentStorage<RectangleShapeComponent>& _rectangleShapeComponents;
    Filter _playerFilter, _meteorFilter, _bulletFilter;
    // Мы хотим изменять position, которое кладем в
// public:
    RenderSystem(World &world)
    : ISystem(world),
    _transformComponents(world.GetStorage<TransformComponent>()),
    _circleShapeComponents(world.GetStorage<CircleShapeComponent>()),
    _rectangleShapeComponents(world.GetStorage<RectangleShapeComponent>()),
    _playerFilter(FilterBuilder(world).With<TransformComponent>().With<PlayerComponent>().Build()),
    _meteorFilter(FilterBuilder(world).With<TransformComponent>().With<MeteorComponent>().Build()),
    _bulletFilter(FilterBuilder(world).With<TransformComponent>().With<BulletComponent>().Build()) {
        std::cout << "RenderSystem\n";
    }

    void OnInit() override { }

    void NotifyKeyboardEvent(sf::Keyboard::Key buttonCode) override { }

    void OnUpdate(sf::RenderWindow& window, std::shared_ptr<Text> text) override {
        // для главной единицы игрока (ГЕИ)
        for (const auto ent : _playerFilter) {
            if (!world.IsEntityAlive(ent)) continue;

            auto& transform = _transformComponents.Get(ent);
            auto& circle = _circleShapeComponents.Get(ent);
            circle._polygon.setPosition({
                transform.position.x,
                transform.position.y
            });
            circle._polygon.rotate(transform.rotationSpeed);
            window.draw(circle._polygon);
            // std::cout << ent << " Pos triangle: " << transform.position.x << " " << transform.position.y << std::endl;
        }
        // для метеоритов
        for (const auto ent : _meteorFilter) {
            if (!world.IsEntityAlive(ent)) continue;

            auto& transform = _transformComponents.Get(ent);
            auto& polygon = _circleShapeComponents.Get(ent);
            polygon._polygon.setPosition({
                transform.position.x,
                transform.position.y
            });
            polygon._polygon.rotate(transform.rotationSpeed);
            window.draw(polygon._polygon);
            // std::cout << ent << " Pos rect: " << transform.position.x << " " << transform.position.y << std::endl;
        }
        // для пуль
        for (const auto ent : _bulletFilter) {
            if (!world.IsEntityAlive(ent)) continue;

            auto& transform = _transformComponents.Get(ent);
            auto& rectangle = _rectangleShapeComponents.Get(ent);
            if (ent == 1) {
                std::cout << transform.position.x << ", " << transform.position.y << "; " << transform.speed.x << ", " << transform.speed.y << std::endl;
            }
            rectangle._rectangle.setPosition({
                transform.position.x,
                transform.position.y
            });
            rectangle._rectangle.setRotation(transform.rotationSpeed);
            window.draw(rectangle._rectangle);
            // std::cout << ent << " Pos triangle: " << transform.position.x << " " << transform.position.y << std::endl;
        }
    }
};

#endif //RENDER_SYSTEM_H