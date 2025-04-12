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
        _componentStorages.reserve(4);
    }

    template <typename T>
    FilterBuilder& With() {
        auto storage = _world.GetRawStorage<T>();
        _componentStorages.push_back(storage);

        return *this;
    }

    Filter Build() const {
        return Filter(_world, _componentStorages); 
    }
};

#endif //FILTER_BUILDER_H