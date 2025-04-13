#ifndef COMPONENT_STORAGE_H
#define COMPONENT_STORAGE_H

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

    void Resize(const int sparseSize, const int dataSize);


public:
    World& _world;
    ComponentStorage() {
        Resize(64, 64);
    };
    ComponentStorage(World& world):_world(world) {
        Resize(64, 64);
    };
    ComponentStorage(World& world, int storagesCount):_world(world) {
        Resize(storagesCount, storagesCount);
    };


    bool Has(const int entityIid);
    T& Get(const int entityIid);
    void Add(const int entityIid, const T& value);
    void Remove(const int entityIid);
    const std::span<const T> All();
    const std::span<const int> Entities();
    int Count();
};

#endif //COMPONENT_STORAGE_H