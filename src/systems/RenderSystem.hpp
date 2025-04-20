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

class RenderSystem final : public ISystem {
public:
    ComponentStorage<Position>& _positionComponents;
    ComponentStorage<TransformComponent>& _transformComponents;
    ComponentStorage<RectangleShapeComponent>& _rectangleShapeComponents;
    ComponentStorage<TriangleShapeComponent>& _triangleShapeComponents;
    Filter _positioningRectangle, _positioningTriangle;
    // Мы хотим изменять position, которое кладем в
// public:
    RenderSystem(World &world)
    : ISystem(world),
    _positionComponents(world.GetStorage<Position>()),
    _transformComponents(world.GetStorage<TransformComponent>()),
    _rectangleShapeComponents(world.GetStorage<RectangleShapeComponent>()),
    _triangleShapeComponents(world.GetStorage<TriangleShapeComponent>()),
    _positioningRectangle(FilterBuilder(world).With<TransformComponent>().With<RectangleShapeComponent>().Build()),
    _positioningTriangle(FilterBuilder(world).With<TransformComponent>().With<TriangleShapeComponent>().Build()) {
        std::cout << "RenderSystem";
    }

    void OnInit() override { }

    void OnUpdate(sf::RenderWindow& window) override {
        window.clear();
        for (const auto ent : _positioningRectangle) {
            //auto& position = _positionComponents.Get(ent);
            auto& transform = _transformComponents.Get(ent);
            auto& rectangle = _rectangleShapeComponents.Get(ent);
            rectangle._rectangle.setPosition({transform.position.x, transform.position.y});
            window.draw(rectangle._rectangle);
            std::cout << ent << " Pos: " << transform.position.x << " " << transform.position.y << std::endl;
        
        }
        for (const auto ent : _positioningTriangle) {
            //auto& position = _positionComponents.Get(ent);
            auto& transform = _transformComponents.Get(ent);
            auto& triangle = _triangleShapeComponents.Get(ent);
            triangle._triangle.setPosition({transform.position.x, transform.position.y});
            window.draw(triangle._triangle);
            std::cout << ent << " Pos: " << transform.position.x << " " << transform.position.y << std::endl;
        
        }
        window.display();
    }
};

#endif //RENDER_SYSTEM_H