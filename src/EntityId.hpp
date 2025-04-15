#ifndef ENTITY_ID_HPP
#define ENTITY_ID_HPP

#include <vector>
#include <string>
#include <iostream>
#include <memory>

class EntityId {
    std::vector<int> _components;
    int _gen;

public:
    const int Id;
    EntityId(const int id, const int gen) : _gen(gen), Id(id) {
        _components.reserve(6); // под энтити резервируем 6 компонент
    }

    void AddComponent(int component) {
        _components.push_back(component);
    };

    int RemoveComponent(int component) {
        for (int i = 0; i < _components.size(); i++) {
            if (_components[i] == component && i < _components.size() - 1)
                _components[i] = _components[_components.size() - 1];
        }
        _components.pop_back();
        return _components.size() - 1;
    };

    bool IsRemoved() const {
        return _gen < 0;
    };

    const std::vector<int>& Components() const {
        return _components;
    };

    int Gen() const {
        return _gen;
    };

    void Remove() {
        _gen = -(_gen+1);
        _components.clear();
    };

    void Recycle() {
        _gen *= -1;
    };

    bool Equals(const EntityId &other) const {
        return Id == other.Id && _gen == other._gen;
    };

    bool operator ==(const EntityId& other) const;
    bool operator !=(const EntityId& other) const;
    friend std::ostream& operator<<(std::ostream& os, const EntityId& eId);
};


#endif //ENTITY_ID_HPP