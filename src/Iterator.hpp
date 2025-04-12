#ifndef ITERATOR_H
#define ITERATOR_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <span>
#include "BaseComponentStorage.h"

class Iterator {
    const std::span<const int> _minStorageEntities;
    const std::vector<std::shared_ptr<BaseComponentStorage>>& _storages;
    const size_t _minStorageIndex;
    int _currentEntity;
    size_t _current;

public:
    using iterator_category = std::input_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using pointer = int*; // или value_type*, для input не нужно
    using reference = int&; // или value_type&, для input не нужно

    // Ищем первую сущность, в _minStorageEntities, которая будет содержаться во всех хранилищах из _storages, и записываем в _currentEntity 
    Iterator(
        size_t current,
        std::span<const int> minStorageEntities,
        const std::vector<std::shared_ptr<BaseComponentStorage>>& storages,
        size_t minStorageIndex
    ):
    _current(current),
    _minStorageEntities(minStorageEntities),
    _storages(storages),
    _minStorageIndex(minStorageIndex)
    {
        while (_current < _minStorageEntities.size()) {
            int entity = _minStorageEntities[_current];
            bool valid = true;

            for (const auto& storage : _storages) {
                if (!storage->Has(entity)) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                _currentEntity = entity;
                return;
            }

            ++_current;
        }

        _currentEntity = -1;
    }

    bool HasAllComponents() const {
        for (const auto& storage : _storages) {
            if (!storage->Has(_currentEntity)) {
                return false;
            }
        }
        return true;
    }

    value_type operator*() const { 
        return _currentEntity; 
    }
    // Префиксный инкремент
    Iterator& operator++() {
        while (++_current < _minStorageEntities.size()) {
            _currentEntity = _minStorageEntities[_current];
            if (HasAllComponents())
                break;
        }
        return *this;
    }
    // Оператор сравнения
    bool operator!=(const Iterator& other) const { 
        return _current != other._current;
    }
};

#endif //ITERATOR_H