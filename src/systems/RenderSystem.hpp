#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "../ComponentStorage.hpp"
#include "../components/Position.h"
#include "../IInitializer.hpp"
#include "../Filter.hpp"
#include "../FilterBuilder.hpp"
#include "../components/RectangleShapeComponent.h"

class RenderSystem final : public ISystem {
public:
    ComponentStorage<Position>& _positionComponents;
    ComponentStorage<RectangleShapeComponent>& _rectangleShapeComponents;
    Filter _positioningRectangle;
    // Мы хотим изменять position, которое кладем в
// public:
    RenderSystem(World &world)
    : ISystem(world),
    _positionComponents(world.GetStorage<Position>()),
    _rectangleShapeComponents(world.GetStorage<RectangleShapeComponent>()),
    _positioningRectangle(FilterBuilder(world).With<Position>().With<RectangleShapeComponent>().Build()) {
        std::cout << "RenderSystem";
    }

    void OnInit() override { }

    void OnUpdate(sf::RenderWindow& window) override {
        std::cout << "Govno ebanoe";
        for (const auto ent : _positioningRectangle) {
            auto& position = _positionComponents.Get(ent);
            auto& rectangle = _rectangleShapeComponents.Get(ent);
            rectangle._rectangle.setPosition({position.X, position.Y});
            window.clear();
            window.draw(rectangle._rectangle);
            window.display();
            std::cout << ent << " Pos: " << position.X << std::endl;
        }
    }
};

#endif //RENDER_SYSTEM_H