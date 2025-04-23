#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>
#include "BaseComponentStorage.h"
#include "ComponentStorage.hpp"
#include "EntityId.hpp"
#include "components/Position.h"

class World {
    const int DefaultEntitiesCapacity = 64; // в мире за раз может быть 64 сущности по дефолту (без перераспределения памяти)
    std::vector<EntityId> _entities; // сущности
    std::vector<int> _freeEntities; // удалённые индексы сущностей
    // отобращение хеша (ключ мапы) на указатель на BaseComponentStorage, нужна для быстрого поиска по хэшу
    std::unordered_map<size_t, std::shared_ptr<BaseComponentStorage>> _componentStoragesHash;
    // массив всех указателей на BaseComponentStorage
    std::vector<std::shared_ptr<BaseComponentStorage>> _componentStorages;
    int _storagesCount = 0;
public:
    World() = default;
    sf::RenderWindow& window;
    World(sf::RenderWindow& _window) : window(_window) {}
    int CreateEntity() {
        int entityId;
        if (!_freeEntities.empty()) {
            entityId = _freeEntities.back();
            _freeEntities.pop_back();
            _entities[entityId].Recycle();
        }
        else {
            entityId = _entities.size();
            _entities.emplace_back(entityId, 1); // вставляем
        }
        return entityId;
    };

    void RemoveEntity(int ent) {
        auto& entity = _entities[ent];

        if (entity.IsRemoved())
            return;

        const auto& components = entity.Components();
        if (!components.empty()) {
            for (int i = components.size() - 1; i >= 0; i--)
                _componentStorages[components[i]]->Remove(ent);
        }
        else {
            entity.Remove();
            _freeEntities.push_back(entity.Id);
        }
    };

    EntityId GetPackedEntity(int e) const {
        return _entities[e];
    }

    bool UnpackEntity(const EntityId& eId, int& e) const {
        e = eId.Id;
        return IsEntityAlive(e) && eId.Gen() == _entities[e].Gen();
    }

    bool IsEntityAlive(int e) const {
        auto& entity = _entities[e];
        return !entity.IsRemoved() && entity.Id > 0 && entity.Id < _entities.size() && e == entity.Id;
    }

    void EntityComponentsChanged(int e, int storageId, bool added) {
        auto& entity = _entities[e];

        if (added) {
            entity.AddComponent(storageId);
        }
        else {
            const int newComponentsCount = entity.RemoveComponent(storageId);
            if (newComponentsCount == 0)
                RemoveEntity(e);
        }
    };

    // получаем ComponentStorage для определённого типа компонента по хэшу или добавляем в _componentStoragesHash
    // новый указатель на ComponentStorage
    template <typename T>
    std::shared_ptr<ComponentStorage<T>> GetRawStorage() {
        const auto typeHash = typeid(T).hash_code(); // берём хэш от типа компонента (например, Position)
        const auto foundStorageIterator = _componentStoragesHash.find(typeHash); // итератор по _componentStoragesHash

        // .end() - флаг (прошли по всему списку), != .end() => мы что-то нашли
        if (foundStorageIterator != _componentStoragesHash.end())
            return std::static_pointer_cast<ComponentStorage<T>>(foundStorageIterator->second); // second - это значение, first - ключ

        // не нашли никакой указатель на storage с данным типом данных T

        int storagesCount = _componentStorages.size();
        auto storage = std::make_shared<ComponentStorage<T>>(*this, storagesCount);
        // кастим обратно в BaseComponentStorage, чтобы положить это в вектор
        //_componentStoragesHash.insert({typeHash, std::static_pointer_cast<BaseComponentStorage>(storage)});
        _componentStoragesHash.insert({typeHash, storage});

        // перераспределение capacity
        if (storagesCount == _componentStorages.capacity()) {
            const int newSize = _storagesCount << 1; // увеличиваем капасити в 2 раза
            _componentStorages.reserve(newSize);
        }

        // добавляем указатель на новое хранилище компонент
        //_componentStorages.push_back(std::static_pointer_cast<BaseComponentStorage>(storage));
        _componentStorages.push_back(storage);

        return storage;
    }

    template <typename T>
    ComponentStorage<T>& GetStorage() {
        return *GetRawStorage<T>();
    };
};

#endif //WORLD_H