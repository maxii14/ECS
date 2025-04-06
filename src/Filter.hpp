#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "BaseComponentStorage.h"
#include "Iterator.hpp"
#include "World.hpp"

class Filter {
    std::vector<std::shared_ptr<BaseComponentStorage>> _componentStorages;
    size_t _minStorageIndex = -1;
    size_t FindMinComponentStorage() const {
        size_t minIndex = 0;
        size_t minCount = _componentStorages[0]->Count();
    
        for (size_t i = 1; i < _componentStorages.size(); ++i) {
            size_t count = _componentStorages[i]->Count();
            if (count < minCount) {
                minCount = count;
                minIndex = i;
            }
        }
    
        return minIndex;
    }

public:
    Filter(World& _, const std::vector<std::shared_ptr<BaseComponentStorage>>& componentStorages)
    : _componentStorages(componentStorages) { 

    }

    Iterator begin() {
        _minStorageIndex = FindMinComponentStorage();
        const auto& minStorage = _componentStorages[_minStorageIndex];
        return Iterator(0, minStorage->Entities(), _componentStorages);
    }

    Iterator end() {
        const auto& minStorage = _componentStorages[_minStorageIndex];
        return Iterator(minStorage->Entities().size(), minStorage->Entities(), _componentStorages);
    }
};

#endif //FILTER_H