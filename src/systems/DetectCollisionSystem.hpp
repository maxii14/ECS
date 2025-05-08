#ifndef DETECT_COLLISION_SYSTEM_H
#define DETECT_COLLISION_SYSTEM_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "../ComponentStorage.hpp"
#include "../components/Position.h"
#include "../components/BoxColliderComponent.h"
#include "../components/CircleColliderComponent.h"
#include "../components/CollisionComponent.h"
#include "../IInitializer.hpp"
#include "../Filter.hpp"
#include "../FilterBuilder.hpp"

class DetectCollisionSystem final : public ISystem {
public:
    ComponentStorage<BoxColliderComponent>& _boxComponents;
    ComponentStorage<CircleColliderComponent>& _circleComponents;
    ComponentStorage<CollisionComponent>& _collisionComponents;
    Filter _meteors;
    Filter _playerAndBullets;

// public:
    DetectCollisionSystem(World &world)
    : ISystem(world),
    _boxComponents(world.GetStorage<BoxColliderComponent>()),
    _circleComponents(world.GetStorage<CircleColliderComponent>()),
    _collisionComponents(world.GetStorage<CollisionComponent>()),
    _meteors(FilterBuilder(world).With<CircleColliderComponent>().Build()),
    _playerAndBullets(FilterBuilder(world).With<BoxColliderComponent>().Build()) {
        std::cout << "DetectCollisionSystem\n";
    }

    void OnInit() override { }

    void NotifyKeyboardEvent(sf::Keyboard::Key buttonCode) override { }

    void OnUpdate(sf::RenderWindow& window) override {
        for (const auto pObject : _playerAndBullets) {
            if (!world.IsEntityAlive(pObject)) continue; // считаем коллизии только с "живыми" объектами

            for (const auto nObject : _meteors) {
                if (!world.IsEntityAlive(nObject)) continue;

                auto& circleCollider = _circleComponents.Get(nObject);
                auto& boxCollider = _boxComponents.Get(pObject);
                auto& pCollisionComponent = _collisionComponents.Get(pObject);
                auto& nCollisionComponent = _collisionComponents.Get(nObject);

                // вычисляем ближайшую точку к кругу на ААВВ
                float clampledX = std::clamp(circleCollider._refPoint.x, boxCollider._refPoint.x - boxCollider._xSize / 2.f, boxCollider._refPoint.x + boxCollider._xSize / 2.f);
                float clampledY = std::clamp(circleCollider._refPoint.y, boxCollider._refPoint.y - boxCollider._ySize / 2.f, boxCollider._refPoint.y + boxCollider._ySize / 2.f);
                bool collides = (clampledX - circleCollider._refPoint.x) * (clampledX - circleCollider._refPoint.x) + (clampledY - circleCollider._refPoint.y) * (clampledY - circleCollider._refPoint.y) <= circleCollider._radius * circleCollider._radius;
                if (collides) {
                    std::cout << "POPA DANIE\n";
                    pCollisionComponent.collisionWithComponents.push_back(nObject);
                    nCollisionComponent.collisionWithComponents.push_back(pObject);
                }
            }
        }
    }
};

#endif //DETECT_COLLISION_SYSTEM_H