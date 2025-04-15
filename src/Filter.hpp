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

    // Находим индекс componentStorage'a с минимальным Count(), т.е. с минимальным числом элементов
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
    Filter(
        World& _,
        const std::vector<
            std::shared_ptr<BaseComponentStorage>
        >& componentStorages)
    : _componentStorages(componentStorages) {

    }

    Iterator begin() {
        _minStorageIndex = FindMinComponentStorage();
        const auto& minStorageEntities = _componentStorages[_minStorageIndex]->Entities();
        const int current = 0;
        return Iterator(current, minStorageEntities, _componentStorages, _minStorageIndex);

        // _minStorageIndex = FindMinComponentStorage();
        // const auto& minStorage = _componentStorages[_minStorageIndex];
        // return Iterator(0, minStorage->Entities(), _componentStorages);
    }

    Iterator end() {
        const auto& minStorage = _componentStorages[_minStorageIndex];
        return Iterator(minStorage->Entities().size(), minStorage->Entities(), _componentStorages, _minStorageIndex);
    }
};

#endif //FILTER_H