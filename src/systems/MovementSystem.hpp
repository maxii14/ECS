#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include <memory>
#include <vector>
#include <string>
#include <iostream>

#include "../Filter.hpp"
#include "../IInitializer.hpp"
#include "../FilterBuilder.hpp"
#include "../ComponentStorage.hpp"

#include "../components/Position.h"
#include "../components/BoxColliderComponent.h"
#include "../components/CircleColliderComponent.h"
#include "../components/TransformComponent.h"


class MovementSystem final : public ISystem {
public:
    ComponentStorage<Position>& _positionComponents;
    ComponentStorage<TransformComponent>& _transformComponents;
    ComponentStorage<BoxColliderComponent>& _boxColliderComponents;
    ComponentStorage<CircleColliderComponent>& _circleColliderComponents;

    Filter _transformingBox;
    Filter _transformingCircle;

    MovementSystem(World &world)
    : ISystem(world),
    _positionComponents(world.GetStorage<Position>()),
    _transformComponents(world.GetStorage<TransformComponent>()),
    _boxColliderComponents(world.GetStorage<BoxColliderComponent>()),
    _circleColliderComponents(world.GetStorage<CircleColliderComponent>()),
    _transformingBox(FilterBuilder(world).With<TransformComponent>().With<BoxColliderComponent>().Build()),
    _transformingCircle(FilterBuilder(world).With<TransformComponent>().With<CircleColliderComponent>().Build()){
        std::cout << "MovementSystem\n";
    }

    void OnInit() override { }

    void NotifyKeyboardEvent(sf::Keyboard::Key buttonCode) override { }

    void OnUpdate(sf::RenderWindow& window) override {
        UpdatePosition(_transformingBox, _boxColliderComponents);
        UpdatePosition(_transformingCircle, _circleColliderComponents);
    }

    template <typename T>
    void UpdatePosition(Filter filter, ComponentStorage<T>& componentStorage){
        for (const auto ent : filter) {
            auto& transform = _transformComponents.Get(ent);
            auto& collider = componentStorage.Get(ent);
            transform.position += transform.speed;
            collider._refPoint += transform.speed;
        }
    }
};

#endif //MOVEMENT_SYSTEM_H