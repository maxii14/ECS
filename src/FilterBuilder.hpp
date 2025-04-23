#ifndef FILTER_BUILDER_H
#define FILTER_BUILDER_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "BaseComponentStorage.h"
#include "World.hpp"
#include "Filter.hpp"

class FilterBuilder {
    World& _world;
    std::vector<std::shared_ptr<BaseComponentStorage>> _componentStorages;
    
public:
    FilterBuilder(World& world) : _world(world) {
        std::cout << "not reserved";
        _componentStorages.reserve(4);
        std::cout << "reserved";
    }

    template <typename T>
    FilterBuilder& With() {
        std::cout << "AA";
        auto storage = _world.GetRawStorage<T>();
        std::cout << "BB";
        //std::static_pointer_cast<ComponentStorage<T>>(storage)
        _componentStorages.push_back(storage);

        return *this;
    }

    Filter Build() const {
        return Filter(_world, _componentStorages); 
    }
};

#endif //FILTER_BUILDER_H