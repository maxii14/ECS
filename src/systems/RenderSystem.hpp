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
#include "../components/TriangleShapeComponent.h"
#include "../components/PolygonShapeComponent.h"

class RenderSystem final : public ISystem {
public:
    ComponentStorage<TransformComponent>& _transformComponents;
    ComponentStorage<PolygonShapeComponent>& _polygonShapeComponents;
    ComponentStorage<RectangleShapeComponent>& _rectangleShapeComponents;
    ComponentStorage<TriangleShapeComponent>& _triangleShapeComponents;
    Filter _positioningPolygon, _positioningTriangle, _positioningRectangle;
    // Мы хотим изменять position, которое кладем в
// public:
    RenderSystem(World &world)
    : ISystem(world),
    _transformComponents(world.GetStorage<TransformComponent>()),
    _polygonShapeComponents(world.GetStorage<PolygonShapeComponent>()),
    _triangleShapeComponents(world.GetStorage<TriangleShapeComponent>()),
    _rectangleShapeComponents(world.GetStorage<RectangleShapeComponent>()),
    _positioningPolygon(FilterBuilder(world).With<TransformComponent>().With<PolygonShapeComponent>().Build()),
    _positioningTriangle(FilterBuilder(world).With<TransformComponent>().With<TriangleShapeComponent>().Build()),
    _positioningRectangle(FilterBuilder(world).With<TransformComponent>().With<RectangleShapeComponent>().Build()) {
        std::cout << "RenderSystem";
    }

    void OnInit() override { }

    void OnUpdate(sf::RenderWindow& window) override {
        window.clear();
        // для метеоритов
        for (const auto ent : _positioningPolygon) {
            auto& transform = _transformComponents.Get(ent);
            auto& polygon = _polygonShapeComponents.Get(ent);
            polygon._polygon.setPosition({transform.position.x, transform.position.y});
            polygon._polygon.rotate(transform.rotationSpeed);
            window.draw(polygon._polygon);
            // std::cout << ent << " Pos rect: " << transform.position.x << " " << transform.position.y << std::endl;
        }
        // для главной единицы игрока (ГЕИ)
        for (const auto ent : _positioningTriangle) {
            auto& transform = _transformComponents.Get(ent);
            auto& triangle = _triangleShapeComponents.Get(ent);
            triangle._triangle.setPosition({transform.position.x, transform.position.y});
            triangle._triangle.rotate(transform.rotationSpeed);
            window.draw(triangle._triangle);
            // std::cout << ent << " Pos triangle: " << transform.position.x << " " << transform.position.y << std::endl;
        }
        // для пуль
        for (const auto ent : _positioningRectangle) {
            auto& transform = _transformComponents.Get(ent);
            auto& rectangle = _rectangleShapeComponents.Get(ent);
            rectangle._rectangle.setPosition({transform.position.x, transform.position.y});
            rectangle._rectangle.setRotation(transform.rotationSpeed);
            window.draw(rectangle._rectangle);
            // std::cout << ent << " Pos triangle: " << transform.position.x << " " << transform.position.y << std::endl;
        }
        window.display();
    }
};

#endif //RENDER_SYSTEM_H