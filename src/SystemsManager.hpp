#ifndef SYSTEMS_MANAGER_H
#define SYSTEMS_MANAGER_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "World.hpp"
#include "IInitializer.hpp"

#include <SFML/Graphics.hpp>

class SystemsManager {
public:
    std::vector<std::shared_ptr<IInitializer>> _newInitializers;
    std::vector<std::shared_ptr<IInitializer>> _initializers;
    std::vector<std::shared_ptr<ISystem>> _systems;
    World& _world;

//public:
    SystemsManager(World& world) : _world(world) { }
    SystemsManager& AddInitializer(std::shared_ptr<IInitializer> initializer) {
        _newInitializers.push_back(initializer);
        return *this;
    };

    SystemsManager& AddSystem(std::shared_ptr<ISystem> system) {
        _systems.push_back(system);
        return *this;
    };

    void Initialize() {
        if (_newInitializers.empty()) return;
        for (int i = 0; i < _newInitializers.size(); i++) {
            _newInitializers[i]->OnInit();
            _initializers.push_back(_newInitializers[i]);
        }

        _newInitializers.clear();

        // KAKASHKA ALERT!!!!!!!!!!!!!!!!!
        for (int i = 0; i < _systems.size(); i++) {
            _systems[i]->OnInit();
        }
        // KAKASHKA ALERT!!!!!!!!!!!!!!!!!

    };

    void Update(sf::RenderWindow& window) {
        Initialize();

        for (int i = 0; i < _systems.size(); i++) {
            _systems[i]->OnUpdate(window);
        }
    };

    void NotifyKeyboardEvent(sf::Keyboard::Key buttonCode) {
        for (int i = 0; i < _systems.size(); i++) {
            _systems[i]->NotifyKeyboardEvent(buttonCode);
        }
    }
};

#endif //SYSTEMS_MANAGER_H