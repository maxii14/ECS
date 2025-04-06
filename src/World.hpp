#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>
#include "BaseComponentStorage.h"
#include "ComponentStorage.h"
#include "EntityId.hpp"

class World {
    const int DefaultEntitiesCapacity = 64;
    std::vector<EntityId> _entities; 
    std::vector<int> _freeEntities;
    std::unordered_map<size_t, std::shared_ptr<BaseComponentStorage>> _componentStoragesHash;
    std::vector<std::shared_ptr<BaseComponentStorage>> _componentStorages; int _storagesCount = 0;
public:
    World() = default;
    int CreateEntity() {
        int entityId;
        if (!_freeEntities.empty()) {
            entityId = _freeEntities.back();
            _freeEntities.pop_back();
            _entities[entityId].Recycle();
        }
        else {
            entityId = _entities.size();
            _entities.emplace_back(entityId, 1);
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

    template <typename T> std::shared_ptr<ComponentStorage<T>> GetRawStorage();
    template <typename T> ComponentStorage<T>& GetStorage() {
        const auto typeHash = typeid(T).hash_code();
        const auto foundStorageIterator = _componentStoragesHash.find(typeHash);

        if (foundStorageIterator != _componentStoragesHash.end())
            return *std::static_pointer_cast<ComponentStorage<T>>(foundStorageIterator->second);
        
        int storagesCount = _componentStorages.size();
        auto storage = std::make_shared<ComponentStorage<T>>(*this, storagesCount);
        _componentStoragesHash.insert({typeHash, storage});

        if (storagesCount == _componentStorages.capacity()) {
            const int newSize = _storagesCount << 1;
            _componentStorages.reserve(newSize);
        }

        _componentStorages.push_back(storage);
        return *storage;
    };
};

#endif //WORLD_H