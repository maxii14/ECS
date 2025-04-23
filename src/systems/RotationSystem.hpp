#ifndef ROTATION_SYSTEM_H
#define ROTATION_SYSTEM_H

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

class RotationSystem final : public ISystem {
public:
    ComponentStorage<TransformComponent>& _transformComponents;
    Filter _transforming;

// public:
    RotationSystem(World &world)
    : ISystem(world),
    _transformComponents(world.GetStorage<TransformComponent>()),
    _transforming(FilterBuilder(world).With<TransformComponent>().Build()) {
        std::cout << "RotationSystem";
    }

    void OnInit() override { }

    void OnUpdate(sf::RenderWindow& window) override {
        for (const auto ent : _transforming) {
            auto& transform = _transformComponents.Get(ent);
            if (transform.canManuallyRotate) 
            {
                transform.rotationSpeed = sf::degrees(0);
                while (const std::optional event = world.window.pollEvent())
                {
                    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                    {
                        std::wcout << L"Key pressed with code = " << sf::Keyboard::getDescription(keyPressed->scancode).toWideString() << "\n";

                        if (keyPressed->code == sf::Keyboard::Key::Left)
                        {
                            transform.rotationSpeed = sf::degrees(-5);
                        }
                        if (keyPressed->code == sf::Keyboard::Key::Right)
                        {
                            transform.rotationSpeed = sf::degrees(5);
                        }
                    }
                }
            }
        }
    }
};

#endif //ROTATION_SYSTEM_H