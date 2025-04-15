#ifndef COMPONENT_STORAGE_HPP
#define COMPONENT_STORAGE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "ConfigReader.h"
#include "BaseComponentStorage.h"
//#include "World.hpp"

class World;

template <typename T>
class ComponentStorage : public BaseComponentStorage {
    std::vector<T> _data; // Для плотного хранения данных
    std::vector<int> _sparse; // Для разреженного хранения индексов элементов (сущностей)
    std::vector<int> _dense; // Для плотного хранения реально существующих элементов (сущностей, на которых есть компоненты)

    int _count; // Текущее число элементов

    void Resize(const int sparseSize, const int dataSize) {
        int oldSparseSize = _sparse.size();
        if (oldSparseSize < sparseSize) {
            _sparse.resize(sparseSize);
            std::fill_n(_sparse.data() + oldSparseSize, sparseSize - oldSparseSize, -1);
        }

        int oldDataSize = _dense.size();
        if (oldDataSize < dataSize) {
            _dense.resize(dataSize);
            _data.resize(dataSize);
            std::fill_n(_dense.data() + oldDataSize, dataSize - oldDataSize, -1);
        }
    };


public:
    World& _world;
    int a = 5;
    ComponentStorage() {
        _count = 0;
        Resize(64, 64);
    };
    // ComponentStorage(World& world):_world(world) {
    //     _count = 0;
    //     Resize(64, 64);
    // };
    ComponentStorage(World& world, int storagesCount):_world(world) {
        _count = -1;
        Resize(storagesCount, storagesCount);
    };


    bool Has(const int entityIid) const override {
        return entityIid < _sparse.size() && _sparse[entityIid] != -1;
    };
    T& Get(const int entityIid) {
        return _data[_sparse[entityIid]]; // _sparse[entityIid] - индекс в _data, соответственно получаем компонент из _data по entityIid
    };
    void Add(const int entityIid, const T& value) {
        Resize((entityIid / 64 + 1) * 64, _data.size() == _count + 1 ? _data.size() + 64 : _data.size());
        _count++;
        _data[_count] = value; // кладём в data ссылку на компонент
        _dense[_count] = entityIid; // в _dense в конец кладём entityId
        _sparse[entityIid] = _count; // в sparse в качестве индекса entityId, в качестве значения индекс на _data и _dense
    };
    void Remove(const int entityIid) override {
        int arrayIndex = _sparse[entityIid]; // индекс на _data и _dense (то, что хотим удалить)
        int lastEntityIid = _dense[--_count]; // берём предыдущий entityId
        _data[arrayIndex] = _data[_count];
        _dense[arrayIndex] = lastEntityIid;
        _sparse[lastEntityIid] = arrayIndex;
        _sparse[entityIid] = -1;
    };
    const std::span<const T> All() {
        return std::span(_data.begin(), _count);
    };
    std::span<const int> Entities() const override {
        return std::span(_dense.begin(), _count);
    };
    int Count() const override {
        return _count;
    };
    int Id() const override {
        return 0;
    }
};

#endif //COMPONENT_STORAGE_HPP