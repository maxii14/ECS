#ifndef SYSTEMS_MANAGER_H
#define SYSTEMS_MANAGER_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "World.hpp"
#include "IInitializer.hpp"

class SystemsManager {
    std::vector<std::shared_ptr<IInitializer>> _newInitializers;
    std::vector<std::shared_ptr<IInitializer>> _initializers;
    std::vector<std::shared_ptr<ISystem>> _systems;
    World& _world;

public:
    SystemsManager(World& world) : _world(world) { }
    SystemsManager& AddInitializer(std::shared_ptr<IInitializer> initializer) {

    };

    SystemsManager& AddSystem(std::shared_ptr<ISystem> system){

    };
    
    void Initialize()  {
        if (_newInitializers.empty()) return;

        for (int i = 0; i < _newInitializers.size(); i++) {
            _newInitializers[i]->OnInit();
            _initializers.push_back(_newInitializers[i]);
        }

        _newInitializers.clear();
    };

    void Update() {
        Initialize();

        for (int i = 0; i < _systems.size(); i++) {
            _systems[i]->OnUpdate();
        }
    };
};

#endif //SYSTEMS_MANAGER_H