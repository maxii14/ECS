#include "ComponentStorage.h"
#include <iostream>


template <typename T>
ComponentStorage<T>::ComponentStorage() {
    Resize(64, 64);
}

template <typename T>
void ComponentStorage<T>::Resize(const int sparseSize, const int dataSize) {
    int oldSparseSize = _sparse.size();
    if (oldSparseSize < sparseSize) {
        _sparse.resize(sparseSize);
        std::fill_n(_sparse.data() + oldSparseSize,
        sparseSize - oldSparseSize, -1);
    }

    int oldDataSize = _dense.size();
    if (oldDataSize < dataSize) {
        _dense.resize(dataSize);
        _data.resize(dataSize);
        std::fill_n(_dense.data() + oldDataSize,
        dataSize - oldDataSize, -1);
    }
}

template <typename T>
bool ComponentStorage<T>::Has(const int entityIid) { 
    return entityIid < _sparse.size() && _sparse[entityIid] != -1; 
}

template <typename T>
T& ComponentStorage<T>::Get(const int entityIid) { 
    return _data[_sparse[entityIid]]; 
}

template <typename T>
void ComponentStorage<T>::Add(const int entityIid, const T& value) {
    Resize((entityIid / 64 + 1) * 64, _data.size() == _count + 1 ? _data.size() + 64 : _data.size());
    _data[_count] = value;
    _dense[_count] = entityIid;
    _sparse[entityIid] = _count;
    _count++;
}

template <typename T>
void ComponentStorage<T>::Remove(const int entityIid) {
    int arrayIndex = _sparse[entityIid];
    int lastEntityIid = _dense[--_count];
    _data[arrayIndex] = _data[_count];
    _dense[arrayIndex] = lastEntityIid;
    _sparse[lastEntityIid] = arrayIndex;
    _sparse[entityIid] = -1;
}

template <typename T>
const std::span<const T> ComponentStorage<T>::All() {
    return std::span(_data.begin(), _count);
}

template <typename T>
const std::span<const int> ComponentStorage<T>::Entities() {
    return std::span(_dense.begin(), _count);
}