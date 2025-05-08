#ifndef I_INITIALIZER_H
#define I_INITIALIZER_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "World.hpp"
#include "Text.h"
#include <SFML/Graphics.hpp>

class IInitializer {
protected:
    World& world;

public:
    IInitializer(World &world) : world(world) {

    }

    const World& GetWorld() const {
        return world;
    }

    virtual ~IInitializer() = default;
    virtual void OnInit() = 0;
};

class ISystem : public IInitializer {
public:
    ISystem(World &world) : IInitializer(world) { } ~ISystem() override = default;
    virtual void OnUpdate(sf::RenderWindow& window, std::shared_ptr<Text> text) = 0;
    virtual void NotifyKeyboardEvent(sf::Keyboard::Key buttonCode) = 0;
};

#endif //I_INITIALIZER_H